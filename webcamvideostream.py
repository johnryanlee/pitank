# impot the necessary packages
from threading import Thread
import cv2

class WebcamVideoStream:
	def __init__(self, src=0):
		# initialise the video camera stream and read the first frame
		# from the stream
		print("init")
		self.stream = cv2.VideoCapture(src)
		(self.grabbed, self.frame) = self.stream.read()

		self.stopped = False

	def start(self):
		print("start thread")
		t = Thread(target=self.update, args=())
		t.daemon = True
		t.start()
		return self

	def update(self):
		print("read")
		while True:
			if self.stopped:
				return

	def read(self):
		return self.frame

	def stop(self):
		self.stopped = True
