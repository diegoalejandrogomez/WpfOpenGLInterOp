using System;
using System.Collections.Generic;
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

namespace WPF
{
    /// <summary>
    /// Interaction logic for SegmentationWindow.xaml
    /// </summary>
    public partial class SegmentationWindow : Window
    {
        public SegmentationWindow()
        {
            InitializeComponent();
            DataContext = this;
        }

        public Int32 QuantityX { get; set; }
        public Int32 QuantityY { get; set; }
            
        private void Ok_Click(object sender, RoutedEventArgs e)
        {
            DialogResult = true;
        }
    }
}
