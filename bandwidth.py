import sys, time
from socket import *
# not privileged port!
HOST = '192.168.1.54'
MY_PORT = 50027

def main():
    if sys.argv[1] == '-u':
        usage()
    if sys.argv[1] == '-s':
        server()
    elif sys.argv[1] == '-c':
        client()
    elif sys.argv[1] == '-setup':
        setup()
    elif sys.argv[1] == '-teardown':
        teardown()
    else:
        usage()

def usage():
    print ('server side: -s')
    print ('client side: -c [host]')
    sys.exit(2)


def server():
    port = MY_PORT
    #create a TCP socket
    s = socket(AF_INET, SOCK_STREAM)
    s.bind((HOST, port))
    s.listen(1)
    print ('Server started')

    while 1:
        conn, addr = s.accept()
    
        while 1:
            data = conn.recv(1024)
            if not data:
                break
            del data
        conn.send('done'.encode())
        conn.close()


def client():

    count = 200000
    host = sys.argv[2]
    
    port = MY_PORT

    testdata = ('a' * 1024).encode()
    start = time.time()
    s = socket(AF_INET, SOCK_STREAM)

    s.connect((HOST, port))

    i = 0
    while i < count:
        i = i+1
        s.send(testdata)
    s.shutdown(1) 

    data = s.recv(1024)
    end = time.time()
    print (data)

    print ('Bandwidth:', round((1024*count*0.001*0.001) / (end-start), 2),'M/sec.')
    

def setup():
    HOST = sys.argv[2]
    PORT = 50027
    total = 0
    for i in range(0, 100):
        s = socket(AF_INET, SOCK_STREAM)
        start = time.time()
        s.connect((HOST, PORT))
        end = time.time()
        total = total + end - start
        s.close()

    print ('setup:'+ str(total * 1000/100) + 'ms')

def teardown():
    HOST = sys.argv[2]
    PORT = 50027
    total = 0
    for i in range(0, 100):
        s = socket(AF_INET, SOCK_STREAM)

        s.connect((HOST, PORT))
        start = time.time()

        s.close()
        end = time.time()
        total = total + end - start

    print (str(total * 1000/100) + 'ms')

main()
