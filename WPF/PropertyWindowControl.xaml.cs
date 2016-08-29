using SimpleEngineTileEditor;
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
using WPF.Model;
using WPF.ViewModel;

namespace WPF
{
    /// <summary>
    /// Interaction logic for PropertyWindowControl.xaml
    /// </summary>
    public partial class PropertyWindowControl : UserControl
    {
        public PropertyWindowControl()
        {
            InitializeComponent();
        }

        private void DataGrid_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            // ... Get SelectedItems from DataGrid.
            var grid = sender as DataGrid;
            if (grid.SelectedItems != null && grid.SelectedItems.Count > 0)
            {
                var selected = grid.SelectedItems[0] as ManagedSimpleLayer;
                ((PaintViewModel)DataContext).SelectedLayer = selected;
            }
        }

        private void TileGrid_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            // ... Get SelectedItems from DataGrid.
            var grid = sender as DataGrid;
            ((PaintViewModel)DataContext).SelectedTiles = new List<TileViewModel>();
            if (grid.SelectedItems != null && grid.SelectedItems.Count > 0)
            {
                foreach (TileViewModel item in grid.SelectedItems)
                {
                    var selected = item;
                    ((PaintViewModel)DataContext).SelectedTiles.Add(selected);
                }
            }
        }
    }
}
