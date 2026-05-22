import mediapipe as mp
import cv2
import time
def state(hands_landmark):
    fingered=0
    if hands_landmark.landmark[8].y<hands_landmark.landmark[6].y:
        fingered+=1
    if hands_landmark.landmark[12].y<hands_landmark.landmark[10].y:
        fingered+=1
    if hands_landmark.landmark[16].y<hands_landmark.landmark[14].y:
        fingered+=1
    if hands_landmark.landmark[20].y<hands_landmark.landmark[18].y:
        fingered+=1
    opne=hands_landmark.landmark[4].x>hands_landmark.landmark[3].x
    if fingered>=3 and opne:
        return 1
    elif hands_landmark.landmark[4].x<hands_landmark.landmark[3].x and hands_landmark.landmark[8].y < hands_landmark.landmark[6].y and hands_landmark.landmark[12].y < hands_landmark.landmark[10].y and hands_landmark.landmark[16].y>hands_landmark.landmark[14].y and hands_landmark.landmark[20].y>hands_landmark.landmark[18].y:
        return 2
    else:
        return 0

mp_hnds=mp.solutions.hands
hands=mp_hnds.Hands()
cap=cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 160)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 120)
timep=time.time()

if not cap :
    print("couldnt open the camera twin")
    exit()
last_state = -1
last_write_time = 0
WRITE_INTERVAL = 0.1
while True:
    timeps=time.time()
    current_time = time.time()
    ret,frame=cap.read()
    rgb=cv2.cvtColor(frame,cv2.COLOR_BGR2RGB)
    result=hands.process(rgb)
    pito=""
        
   
    
    if cv2.waitKey(1) & 0xFF == ord('q') or timeps-timep>10:
        break
    if result.multi_hand_landmarks is not None:
        for hands_landmark in result.multi_hand_landmarks:
                if state(hands_landmark)==0:
                    pito="closed"

                elif state(hands_landmark)==1:
                    pito="opened"
                elif state(hands_landmark)==2:
                    pito="peace"
                if pito != last_state or (current_time - last_write_time) > WRITE_INTERVAL:
                    with open("state.txt","w") as file:
                        if pito=="opened":
                            file.write("1")           #finna use 1 for opened and 0 for closed
                        elif pito=="closed":
                            file.write("0") 
                        elif pito=="peace":
                            file.write("2")
                        last_state = pito
                        last_write_time = current_time
                mp.solutions.drawing_utils.draw_landmarks(frame,hands_landmark,mp_hnds.HAND_CONNECTIONS)
    print(f"dis nigga hands are ? {pito}")
    
    cv2.imshow("webcame",frame)
cap.release()
cv2.destroyAllWindows()

