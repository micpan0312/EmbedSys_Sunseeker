import serial

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout = 1)
    ser.flush()
    
    dist_txt = open("/home/mp/id&dist/dist.txt", "w")
    dist_txt.close()
    
    abs_dist_txt = open("/home/mp/id&dist/abs_dist.txt", "w")
    abs_dist_txt.close()
    
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print(line)   
            
            if "winReq" in line:
                dist_txt = open("/home/mp/id&dist/dist.txt", "r")
                dist = dist_txt.read()
                
#                 abs_dist_txt = open("/home/mp/id&dist/dist.txt", "r")
#                 abs_dist = dist_txt.read()
                
#                 print("dist: ", dist)
#                 print("abs_dist: ", abs_dist))
                # print("Pi: serial writing to Arduino...")
                ser.write(bytes("Pi: " + dist, 'UTF-8'))
                # ser.write(bytes(abs_dist, 'UTF-8'))
                
                


                # ser.write(bytes("person " + str(dist), 'UTF-8'))
#             if float(line) > 40:
#                 print("it is over 40, pin13 should light up")
#                 ser.write(b"over 40\n")
#             else:
#                 ser.write(b"below 40\n")
#                 print("it is over 40, pin13 remain low")
                
                
 