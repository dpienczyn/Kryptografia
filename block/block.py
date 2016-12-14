from Crypto.Cipher import AES
import os
from hashlib import md5
import binascii

def getSize(dibheader):
# Get image's dimensions (at offsets 4 and 8 of the DIB header)
    DIBheader = []
    for i in range(0,80,2):
        DIBheader.append(int(binascii.hexlify(dibheader)[i:i+2],16))
    width = sum([DIBheader[i+4]*256**i for i in range(0,4)])
    height = sum([DIBheader[i+8]*256**i for i in range(0,4)])
    return (width,height)

def encryptImage(inPath, encMode, outFileName, key):
    blockSize = 16
    fIn = open(inPath, 'rb')
    bmpheader = fIn.read(14)
    dibheader = fIn.read(40)

    fOut = open(outFileName, 'wb')
    fOut.write(bmpheader)
    fOut.write(dibheader)
    width, height = getSize(dibheader)

    raw = (width * height * 3)
    rawPadded = fIn.read(raw)
    rawPadded += (16-len(rawPadded)%16 ) * "!" #padding
    cleartext =  binascii.unhexlify(binascii.hexlify(rawPadded))
    aes = AES.new(key, encMode, os.urandom(16))
    enc = aes.encrypt(cleartext)
    fOut.write(enc)
    fIn.close()
    fOut.close()
    print "Encrypting " + inPath + " using AES  with key = " + key + " to " + outFileName + " done" 

key=""
with open('key.txt', 'r') as keyfile:
    key = keyfile.read().replace('\n', '')

keyMD5 = md5(key).digest()
if len(key) == 16 or len(key) == 24 or len(key) == 32:
    print "key -> " + key   
else:
    print "key -> " + key + "(" + keyMD5+")"
    key = keyMD5
encryptImage("plain.bmp", AES.MODE_ECB, "ecb_crypto.bmp", key)
encryptImage("plain.bmp", AES.MODE_CBC, "cbc_crypto.bmp", key)
print "done!"

