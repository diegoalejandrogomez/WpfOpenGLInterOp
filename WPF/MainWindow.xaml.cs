using SimpleEngineControls;
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
using System.Windows.Navigation;
using System.Windows.Shapes;
using WPF.ViewModel;

namespace WPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            openGlRender.OpenGLControl = new SimpleEngineViewerControl();
            var paintViewModel = new PaintViewModel();
            paintViewModel.OpenGLRenderControl = openGlRender.OpenGLControl;
            DataContext = paintViewModel;
        }

        private void DataGrid_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            // ... Get SelectedItems from DataGrid.
            var grid = sender as DataGrid;
            if(grid.SelectedItems != null && grid.SelectedItems.Count > 0)
            {
                var selected = grid.SelectedItems[0] as ManagedSimpleLayer;
                ((PaintViewModel)DataContext).SelectedLayer = selected;
            }
        }
    }
}
