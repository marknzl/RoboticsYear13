using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SensorUtility
{
    public class SensorValue
    {
        [JsonProperty("sensorPosition")]
        public string SensorPosition { get; set; }

        [JsonProperty("value")]
        public int Value { get; set; }

        [JsonProperty("millis")]
        public int Millis { get; set; }

        [JsonProperty("time")]
        public string Time { get; set; }
    }
}
