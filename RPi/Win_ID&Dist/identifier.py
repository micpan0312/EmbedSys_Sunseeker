import pyrealsense2 as rs
import numpy as np
import cv2
import random
import torch
import time
import sys
# np.set_printoptions(threshold=sys.maxsize)

show_stream = True if len(sys.argv) > 1 and sys.argv[1] == 'show' else False

# model = torch.hub.load('ultralytics/yolov5', 'yolov5s')
# model = torch.hub.load('ultralytics/yolov5', 'yolov5l6')
model = torch.hub.load('ultralytics/yolov5', 'custom', '/home/mp/id&dist/win&all.pt')
# model = torch.hub.load('ultralytics/yolov5', 'custom', '/home/mp/id&dist/win_model.pt')
# model = torch.hub.load('ultralytics/yolov5', 'custom', '/home/mp/id&dist/win_HiRes.pt')

model.conf = 0.5


def isNaN(num):
    return num!= num

def get_abs_dist(box, mid_pos, depth_frame):
    mid_x, mid_y = int(mid_pos[0]), int(mid_pos[1])
    prev_dist = depth_frame.get_distance(mid_x, mid_y)
    
    for y in range(mid_y + 1, 470, 5):
        avg_dist = 0
        if y + 10 < 480:
            dist_list = []
            for i in range(y, y + 10):
                cur_dist = depth_frame.get_distance(mid_x, i)
                if cur_dist:
                    dist_list.append(cur_dist)
                else:
                    dist_list.append(np.nan)
            # avg_dist = np.array(dist_list)
            avg_dist = np.nanmean(np.array(dist_list))
            if avg_dist > prev_dist:
                return prev_dist
            prev_dist = avg_dist
    return prev_dist
    # return depth_frame.get_distance(mid_x, int(box[3]))

def get_mid_pos(frame, box, depth_frame, randnum, show_stream):
    distance_list = []
    mid_pos = [int(box[0] + box[2])//2, int(box[1] + box[3])//2] 
    min_val = min(abs(box[2] - box[0]), abs(box[3] - box[1])) 
    
    for i in range(randnum):
        bias = random.randint(-min_val//16, min_val//16)        

        dist = depth_frame.get_distance(int(mid_pos[0] + bias), int(mid_pos[1] + bias))
        abs_dist = get_abs_dist(box, mid_pos, depth_frame)
        
        # print(dist)
        if show_stream:
            cv2.circle(frame, (int(mid_pos[0] + bias), int(mid_pos[1] + bias)), 4, (255,0,0), -1)
        if dist:
            distance_list.append(dist)
        else:
            distance_list.append(np.nan)
            
    distance_list = np.array(distance_list)
    distance_list = np.sort(distance_list)[randnum//2-randnum//4 : randnum//2+randnum//4] 
    # print(distance_list, np.nanmean(distance_list))
    
    return np.nanmean(distance_list), abs_dist
    
def dectshow(org_img, boxs, depth_frame, show_stream = False):
    img = org_img.copy()
    win_dist_list = []
    win_abs_dist_list = []
    
    for box in boxs:
        # get distance of the box
        dist, abs_dist = get_mid_pos(img, box, depth_frame, 32, show_stream) 
        # print(box)
        # show streaming
        if show_stream:
            cv2.rectangle(img, (int(box[0]), int(box[1])), (int(box[2]), int(box[3])), (0, 255, 0), 2)
            cv2.putText(img, box[-1] + ' ' + str(dist )[:4] + ' m', (int(box[0]), int(box[1])), 0, 1, (255, 255, 255), 2) # cv2.FONT_HERSHEY_SIMPLEX; here font set to option index 0
        print(box[-1], str(dist)[:4] + ' m, abs: ' + str(abs_dist)[:4] + ' m, conf: ',  str(box[4])[:4])
        if box[-1].strip() == 'Window':
            # win_list.append(box[-1])
            win_dist_list.append(str(dist)[:4])
            win_abs_dist_list.append(str(abs_dist)[:4])
    
    return img, win_dist_list, win_abs_dist_list
    
    
if __name__ == "__main__":    
    # Configure depth and color streams
    pipeline = rs.pipeline()
    config = rs.config()
    
    config.enable_stream(rs.stream.depth, 640, 480, rs.format.z16, 30)
    config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)
    
    # Start streaming
    pipeline.start(config)

    align_to = rs.stream.color
    align = rs.align(align_to)
    
    if show_stream: 
        print("Streaming..")
    else:
        print("Not streaming")
    
    try:
        while True:
            # Wait for a coherent pair of frames: depth and color
            frames = pipeline.wait_for_frames()
            # align frams 
            frames = align.process(frames)
            
            depth_frame = frames.get_depth_frame() 
            color_frame = frames.get_color_frame()
            if not depth_frame or not color_frame:
                continue

            # Convert images to numpy arrays
            depth_image = np.asanyarray(depth_frame.get_data())   
            color_image = np.asanyarray(color_frame.get_data()) 

            results = model(color_image)
            boxs= results.pandas().xyxy[0].values
            #boxs = np.load('temp.npy',allow_pickle=True)
            
            box_image, win_dist_list, win_abs_dist_list = dectshow(color_image, boxs, depth_frame, show_stream)
            
            
            if win_dist_list and win_abs_dist_list:
                dist = min(win_dist_list)
                abs_dist = min(win_abs_dist_list)
                
                dist_txt = open("/home/mp/id&dist/dist.txt", "w")
                dist_txt.write("window " + str(dist) + " abs window " + str(abs_dist) + "\n")
                dist_txt.close()
                print("Pi: got window, sending to Arduino...")
            else:
                print("Pi: got no windows...")
                dist_txt = open("/home/mp/id&dist/dist.txt", "w")
                dist_txt.write("no window detected..")
                dist_txt.close()
                
            
            if show_stream:
                # Apply colormap on depth image (image must be converted to 8-bit per pixel first)
                depth_colormap = cv2.applyColorMap(cv2.convertScaleAbs(depth_image, alpha=0.03), cv2.COLORMAP_JET)
                # Stack both images horizontally
                # images = np.hstack((color_image, box_image))
                # Show images
                cv2.namedWindow('RealSense Object Detection', cv2.WINDOW_AUTOSIZE)
                cv2.imshow('RealSense Object Detection', box_image)
                key = cv2.waitKey(1)
                
                # Press esc or 'q' to close the image window
                if key & 0xFF == ord('q') or key == 27:
                    cv2.destroyAllWindows()
                    break
    finally:
        # Stop streaming
        pipeline.stop()
    
#     try:
#         while True:
#             if ser.in_waiting > 0:
#                 line = ser.readline().decode('utf-8').rstrip()
#                 print(line)
#                 
# #                 if "winReq" in line:
# #                     ser.write(b"over 40\n")
# #                 elif "33" in line:
# #                     ser.write(b"just random\n")
#             
#                 # check if window request is needed
#                 # if "winReq" in line:
#                     # Wait for a coherent pair of frames: depth and color
#                 frames = pipeline.wait_for_frames()
#                 # align frams 
#                 frames = align.process(frames)
#                 
#                 depth_frame = frames.get_depth_frame() 
#                 color_frame = frames.get_color_frame()
#                 if not depth_frame or not color_frame:
#                     continue
# 
#                 # Convert images to numpy arrays
#                 depth_image = np.asanyarray(depth_frame.get_data())   
#                 color_image = np.asanyarray(color_frame.get_data()) 
# 
#                 results = model(color_image)
#                 boxs= results.pandas().xyxy[0].values
#                 #boxs = np.load('temp.npy',allow_pickle=True)
#                 
#                 box_image, win_dist_list = dectshow(color_image, boxs, depth_frame, show_stream)
#                 
#                 if win_dist_list:
#                     dist = win_dist_list[0]
#                     print("got winReq, got window distance, about to send dist to Arduino")
#                     win_dist_str = "window " + str(dist) + "\n"
#                     ser.write(bytes(win_dist_str, 'UTF-8'))
#                     # ser.write(b"finally write it huh\n")
#                 else:
#                     ser.write(b"no windows detected, search goes on\n")
#                 
#                 if show_stream:
#                     # Apply colormap on depth image (image must be converted to 8-bit per pixel first)
#                     depth_colormap = cv2.applyColorMap(cv2.convertScaleAbs(depth_image, alpha=0.03), cv2.COLORMAP_JET)
#                     # Stack both images horizontally
#                     # images = np.hstack((color_image, box_image))
#                     # Show images
#                     cv2.namedWindow('RealSense Object Detection', cv2.WINDOW_AUTOSIZE)
#                     cv2.imshow('RealSense Object Detection', box_image)
#                     key = cv2.waitKey(1)
#                     
#                     # Press esc or 'q' to close the image window
#                     if key & 0xFF == ord('q') or key == 27:
#                         cv2.destroyAllWindows()
#                         break
#     finally:
#         # Stop streaming
#         pipeline.stop()
