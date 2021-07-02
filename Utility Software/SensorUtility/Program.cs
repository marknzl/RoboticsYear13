using CsvHelper;
using Newtonsoft.Json;
using SerialProvider;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;

namespace SensorUtility
{
    class Program
    {
        private static List<SensorValue> _topLeftReadings = new List<SensorValue>();
        private static List<SensorValue> _bottomLeftReadings = new List<SensorValue>();
        private static List<SensorValue> _topRightReadings = new List<SensorValue>();
        private static List<SensorValue> _bottomRightReadings = new List<SensorValue>();

        static void Main()
        {
            Console.Title = "Sensor Utility";
            var serialPort = Provider.GetSerialPort();
            var stopWatch = new Stopwatch();
            var startTime = DateTime.Now;

            var readings = new List<SensorValue>();

            if (!Provider.SerialPortExists())
            {
                Console.WriteLine("Serial port doesn't exist!");
                return;
            }

            serialPort.Open();
            bool startedReadings = false;

            var settings = new JsonSerializerSettings()
            {
                NullValueHandling = NullValueHandling.Ignore,
                MissingMemberHandling = MissingMemberHandling.Ignore
            };

            while (true)
            {
                try
                {
                    string message = serialPort.ReadLine();

                    if (message.Contains("Starting"))
                    {
                        startTime = DateTime.Now;
                        Console.WriteLine($"Starting at: {startTime.ToString()}");
                        startedReadings = true;
                    }

                    if (message.Contains("Ending"))
                    {
                        startedReadings = false;
                        break;
                    }

                    if (startedReadings)
                    {
                        Console.WriteLine(message);

                        try
                        {
                            var sensorValue = JsonConvert.DeserializeObject<SensorValue>(message, settings);
                            readings.Add(sensorValue);
                        }
                        catch (JsonException ex)
                        {
                            //
                        }
                    }
                } catch (Exception ex)
                {
                    Console.WriteLine(ex.StackTrace);
                }
            }

            var endTime = DateTime.Now;
            Console.WriteLine($"Ended at: {endTime.ToString()}");

            var csvContent = new StringBuilder();
            csvContent.AppendLine("SensorPosition,Value,Millis,Time");

            for (int i = 0; i < readings.Count; i++)
            {
                var value = readings[i];

                var timeToAdd = TimeSpan.FromMilliseconds(value.Millis);
                var elapsed = stopWatch.Elapsed + timeToAdd;
                value.Time = elapsed.ToString();

                // implement csvhelper later
                if (i == 0)
                {
                    csvContent.AppendLine($"{value.SensorPosition},{value.Value},{value.Millis},{value.Time.ToString()},,Average:,,=AVERAGE(B:B)");
                    continue;
                }

                if (i == 1)
                {
                    csvContent.AppendLine($"{value.SensorPosition},{value.Value},{value.Millis},{value.Time.ToString()},,Std. Deviation:,,=STDEV(B:B)");
                    continue;
                }

                csvContent.AppendLine($"{value.SensorPosition},{value.Value},{value.Millis},{value.Time.ToString()}");
            }

            if (File.Exists("sensor_values.csv"))
                File.Delete("sensor_values.csv");

            File.AppendAllText("sensor_values.csv", csvContent.ToString());
        }

        private static void AddReadingToList(string sensorPosition, SensorValue value)
        {
            if (sensorPosition == "Top left")
            {

            }
        }
    }
}
