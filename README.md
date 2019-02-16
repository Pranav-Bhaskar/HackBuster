# HackBuster
A tool to start a honeypot server on one of your ports and report it.

# Usage
After installation if anyone try's to communicate with the honeypot server it will be saved in the file named report.xml in the root directory.
  
The report.xml is self explanatory.
  
To check if the code is working you can type the command :
  
`telnet 127.0.0.1 51`
  
If this is reported in the xml then it has been installed correctly.
  
If not then raise an issue or contact me.

# Installation
In case you dont have git-cli:
  
`sudo apt install git`
  
Clone the repo :
  
`git clone https://github.com/Pranav-Bhaskar/HackBuster.git`
  
Open the directory :
  
`cd HackBuster`
  
Give Permitions:
  
`sudo chmod 755 install`
  
Give installation command :
  
`sudo ./install`
