using SerialProvider;
using System;

namespace AverageLatency
{
    class Program
    {
        static void Main()
        {
            Console.Title = "Average Latency Tester";
            var serialPort = Provider.GetSerialPort();

            if (!Provider.SerialPortExists())
            {
                Console.WriteLine("Serial port doesn't exist!");
                return;
            }

            serialPort.Open();

            while (true)
            {
                try
                {
                    string message = serialPort.ReadLine();

                    if (message.Contains("Ping"))
                    {
                        serialPort.Write("P");
                    }

                    bool isPing = int.TryParse(message, out int n);
                    if (isPing)
                    {
                        int ping = int.Parse(message);
                        Console.WriteLine($"Average latency: {ping}ms");

                        Console.Write("Restart latency test? (y/n) ");
                        string input = Console.ReadLine().ToLower();

                        if (input == "n")
                            break;

                        Console.Clear();
                    } else
                    {
                        Console.WriteLine(message);
                    }

                } catch (Exception ex)
                {
                    Console.WriteLine(ex.StackTrace);
                }
            }
        }
    }
}
