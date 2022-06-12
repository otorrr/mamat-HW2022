CXX = g++
CXXFLAGS = -Wall -Wextra  -L. -g -std=c++11
RM = rm -f firewall.exe firewall

all : firewall.exe

firewall :
	$(CXX) $(CXXFLAGS) -fPIC -shared field.cpp ip.cpp string.cpp port.cpp -o libfirewall.so
	
firewall.exe : firewall
	$(CXX) $(CXXFLAGS) main.cpp firewall.exe -lfirewall -linput
		
clean : 
	$(RM)
