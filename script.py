import serial
import io
import mysql.connector

ard = serial.Serial('COM3', 9600, timeout=1)
sio = io.TextIOWrapper(io.BufferedRWPair(ard, ard))

def insert(question, answer):
    try:
        db = mysql.connector.connect(
            host = "db.luddy.indiana.edu",
            user = "i494f22_jpyen",
            password = "my+sql=i494f22_jpyen",
            database = "i494f22_jpyen"
        )

        cursor = db.cursor()
        
        sql = '''INSERT INTO response (qid, answer) VALUES (%s, %s)''' % (question, answer)
        cursor.execute(sql)
        db.commit()

        cursor.close()
        db.close()


        # config= {
            #     "user" : "i494f22_jpyen",
            #     "password" : "my+sql=i494f22_jpyen",
            #     "host" : "db.luddy.indiana.edu",
            #     "database" : "i494f22_jpyen"
            # }

        # con = mariadb.connect(**config)  

        # cursor = con.cursor()
        # cursor.execute("INSERT INTO reponse (qid, answer) VALUES (?, ?)", (question, answer))
        # cursor.close()
    except Exception as e:
        print(e)

def pull():
    try:
        db = mysql.connector.connect(
            host = "db.luddy.indiana.edu",
            user = "i494f22_jpyen",
            password = "my+sql=i494f22_jpyen",
            database = "i494f22_jpyen"
        )

        cursor = db.cursor()

        cursor.execute("SELECT q.question as 'Question', r.answer as 'Answer', count(r.answer) as 'Num Answer' from question as q join response as r on r.qid = q.id group by q.id, r.answer order by q.id")
        
        results = cursor.fetchall()
        print(results)    

        for i in results:
            print (i)

    except Exception as e:
        print(e)

while True:
    try:
        sio.flush()

        if sio.read().strip() == 'pull':
            print('Request Pulling')
            pull()
        else:    
            data = [int(i) for i in sio.read().strip().split(':') if i != '']
            for i, v in enumerate(data):
                print("Pushing: {}".format(v))
                insert(i+1, v)
                
    except Exception as e:
        print(e)
