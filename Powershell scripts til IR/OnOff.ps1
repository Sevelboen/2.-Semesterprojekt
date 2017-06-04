$port= new-Object System.IO.Ports.SerialPort COM3,9600,None,8,one
$port.ReadTimeout = 9000
$port.DtrEnable = "true"
$port.open()
Start-Sleep 1.5
$port.Write("POWER")
Start-Sleep 1
$port.Write("LEL")
$port.Close()