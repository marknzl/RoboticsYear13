using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace RobotControl
{
    /// <summary>
    /// Interaction logic for Startscreen.xaml
    /// </summary>
    public partial class Startscreen : Window
    {
        public Startscreen()
        {
            InitializeComponent();

            string[] ports = SerialPort.GetPortNames();
            COMPorts.ItemsSource = ports;
        }

        private void ConnectButton_Click(object sender, RoutedEventArgs e)
        {
            string comPort = COMPorts.Text;
            var mainWindow = new MainWindow(comPort);
            mainWindow.Show();
            this.Close();
        }
    }
}
