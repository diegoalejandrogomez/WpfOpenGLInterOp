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

        private Int32 _quantityX;
        public Int32 QuantityX {
            get {
                return _quantityX;
            }
            set { _quantityX = value; DrawGrid(); }
        }

        private Int32 _quantityY;
        public Int32 QuantityY
        {
            get
            {
                return _quantityY;
            }
            set { _quantityY = value; DrawGrid(); }
        }

        public BitmapImage ImageSource { set; get; }

        private void DrawGrid() {

            previewImage.Children.Clear();

            for (UInt32 i = 0; i < QuantityY-1; ++i) {
                Line l = new Line();
                l.BeginInit();
                l.X1 = 0;
                l.X2 = previewImage.ActualWidth;
                l.Y1 = (i + 1) * (previewImage.ActualHeight/ QuantityY);
                l.Y2 = l.Y1;
                l.Stroke = Brushes.Black;
                l.StrokeThickness = 2;              
                l.EndInit();
                previewImage.Children.Add(l);
              }

            for (UInt32 i = 0; i < QuantityX - 1; ++i)
            {
                Line l = new Line();
                l.BeginInit();
                l.X1 = (i + 1) * (previewImage.ActualWidth / QuantityX);
                l.X2 = l.X1;
                l.Y1 = 0;
                l.Y2 = previewImage.ActualHeight;
                l.Stroke = Brushes.Black;
                l.StrokeThickness = 2;
                l.EndInit();
                previewImage.Children.Add(l);
            }



        }
        private void Ok_Click(object sender, RoutedEventArgs e)
        {
            DialogResult = true;
        }
    }
}
