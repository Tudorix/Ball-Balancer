import cv2
import util
from PIL import Image
import socket
import threading
import time

cap = cv2.VideoCapture(1)

color = [0,255,255] # color in BGR

ESP_IP = "192.168.4.1"
server_port = 80

Socket = None

v = [0,0]

lock = threading.Lock()
running = 1;

def server_loop():
    global running, v

    while running:
        sock = None
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
            sock.settimeout(3)

            print(f"Connecting to {ESP_IP}:{server_port} ...")
            sock.connect((ESP_IP, server_port))
            print("Connected")

            while running:
                with lock:
                    x, y = v[0], v[1]

                message = f"{x},{y}\n"
                sock.sendall(message.encode("utf-8"))

                time.sleep(0.05)   # 20 messages/sec, safer than 50

        except Exception as e:
            print("Socket error:", e)

        finally:
            if sock is not None:
                try:
                    sock.close()
                except:
                    pass

        # wait a bit before reconnecting
        time.sleep(1)


t = threading.Thread(target=server_loop,daemon=True)
t.start()

while running:
    ret, frame = cap.read()
    
    #Crop
    cropped = frame
    frame = cropped
    
    # color detetction
    hsvImage = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    l_lim, h_lim = util.get_limit(color);
    mask = cv2.inRange(hsvImage,l_lim, h_lim) 
    
    # get position
    mask_pil = Image.fromarray(mask)
    box = mask_pil.getbbox()
    
    x1 = 0 
    y1 = 0
    x2 = 0
    y2 = 0
    if box is not None:
        x1, y1, x2, y2 = box; # x1, y1 - TopLeft ; x2,y2 - BotRight
    
    frame = cv2.rectangle(frame,(x1,y1),(x2,y2), (0,255,0),5)
    
    cx = x1 + abs(x2 - x1) // 2 # center X
    cy = y1 + abs(y2 - y1) // 2 # center Y

    with lock:
        v[0] = cx
        v[1] = cy

    
    frame = cv2.circle(frame,(cx,cy),5,(0,0,0),2)
    
    # show image
    cv2.imshow('frame', frame)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        running = 0;
    
        
cap.release()
cv2.destroyAllWindows()