#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist

def twist_callback(twist_message):
#get_caller_id(): Get fully resolved name of local node
	if(twist_message.linear.x>0):
		rospy.loginfo(rospy.get_caller_id() + ": Maju")
	elif(twist_message.linear.x<0):
		rospy.loginfo(rospy.get_caller_id() + ": Mundur")
	elif(twist_message.angular.z>0):
		rospy.loginfo(rospy.get_caller_id() + ": Kiri")
	elif(twist_message.angular.z<0):
		rospy.loginfo(rospy.get_caller_id() + ": Kanan")
	else:
		rospy.loginfo(rospy.get_caller_id() + ": BERHENTI")
	#rospy.loginfo(rospy.get_caller_id() + " NAMA x, y, theta of the robot = %f, %f, %f, %f", twist_message.linear.x,twist_message.angular.x, twist_message.angular.y, twist_message.angular.z)

def listener():
	#inisialisasi node dengan nama turtlesim
	rospy.init_node('Kondisi_Mobil', anonymous=False)

	#deklar Subscriber
	rospy.Subscriber("/cmd_vel", Twist, twist_callback)

	rospy.spin() 

if __name__ == '__main__':
	listener()
