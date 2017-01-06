$port= new-Object System.IO.Ports.SerialPort COM5,115200,None,8,one
$port.open()
:loop
$port.ReadLine()
goto loop
$port.Close()