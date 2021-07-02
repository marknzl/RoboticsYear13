using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace RobotControl
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private static SerialPort serialPort;
        private bool manualControl = false;

        public MainWindow(string comPort)
        {
            InitializeComponent();

            serialPort = new SerialPort(comPort, 9600, Parity.None, 8, StopBits.One);
            serialPort.DataReceived += new SerialDataReceivedEventHandler(SerialPort_DataReceived);
            serialPort.Open();

            if (manualControl)
            {
                ToggleControlButton.Content = "Disable manual control";
            } else
            {
                ToggleControlButton.Content = "Enable manual control";
            }
        }

        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            //Messages.AppendText(serialPort.ReadLine());
            Application.Current.Dispatcher.Invoke(() =>
            {
                string message = serialPort.ReadLine();
                if (message.Contains("ERROR"))
                {
                    MessageBox.Show(message, "Notification", MessageBoxButton.OK, MessageBoxImage.Error);
                }

                if (message.Contains("Pi"))
                {
                    serialPort.Write("P");
                    Application.Current.Dispatcher.Invoke(() =>
                    {
                        serialPort.Write("P");
                    });
                }

                Messages.AppendText(message);
                Messages.ScrollToEnd();
            });
        }

        private void LeftButton_Click(object sender, RoutedEventArgs e)
        {
            serialPort.Write("L");
        }

        private void ForwardButton_Click(object sender, RoutedEventArgs e)
        {
            serialPort.Write("F");
        }

        private void StopButton_Click(object sender, RoutedEventArgs e)
        {
            serialPort.Write("S");
        }

        private void ForkliftUpButton_Click(object sender, RoutedEventArgs e)
        {
            serialPort.Write("T");
        }

        private void ForkliftDownButton_Click(object sender, RoutedEventArgs e)
        {
            serialPort.Write("V");
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            serialPort.Write("B");
        }

        private void RightButton_Click(object sender, RoutedEventArgs e)
        {
            serialPort.Write("R");
        }

        private void ClearMessagesButton_Click(object sender, RoutedEventArgs e)
        {
            Messages.Clear();
        }

        private void ToggleControlButton_Click(object sender, RoutedEventArgs e)
        {
            if (manualControl)
            {
                serialPort.Write("W");
                ToggleControlButton.Content = "Enable manual control";
            }
            else
            {
                serialPort.Write("Q");
                ToggleControlButton.Content = "Disable manual control";
            }

            manualControl = !manualControl;
        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.C)
            {
                Messages.Clear();
            } else
            {
                serialPort.Write(e.Key.ToString().ToUpper());
            }
        }

        private void Window_KeyUp(object sender, KeyEventArgs e)
        {

        }
    }
}
