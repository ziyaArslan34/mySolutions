#-*- coding: utf-8 -*-

import smtplib
import socket
import json
import getpass
import os
from urllib.request import urlopen

username = getpass.getuser()
hostname = socket.gethostname()
ip = socket.gethostbyname(hostname)

url = 'https://ipinfo.io/json'
response = urlopen(url)
data = json.load(response)

message = f"ip = {data['ip']} || sehir = {data['city']} || local = {ip} || hostname = {hostname} || username = {username}"
smtp = smtplib.SMTP("smtp.gmail.com", 587)
smtp.starttls()

sendMail = "sender"
password = input("\nSifre girin: ")
recvMail = "getter"

mainMessage = f"""
	country   : {data['country']}
	city      : {data['city']}
	uname     : {username}
	hostname  : {hostname}
	local ip  : {ip}
	global ip : {data['ip']}
"""

try:
	smtp.login(sendMail, password)
except:
	print("login() error!")
	print(mainMessage)
	exit()

try:
	smtp.sendmail(sendMail, recvMail, mainMessage)
	print("success")
except:
	print("send() error!")
	exit()
