using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SerialProvider
{
    public class Provider
    {
        private static string _port = "COM3";

        public static SerialPort GetSerialPort()
        {
            var portExists = SerialPort.GetPortNames().Any(x => x == _port);
            if (!portExists)
                return null;

            var serialPort = new SerialPort()
            {
                PortName = _port,
                BaudRate = 9600,
                Parity = Parity.None,
                DataBits = 8,
                StopBits = StopBits.One
            };

            return serialPort;
        }

        public static bool SerialPortExists()
        {
            var portExists = SerialPort.GetPortNames().Any(x => x == _port);
            if (portExists)
                return true;

            return false;
        }
    }
}
