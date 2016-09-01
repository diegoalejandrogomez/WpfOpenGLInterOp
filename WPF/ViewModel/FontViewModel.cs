using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SimpleEngineTileEditor;

namespace WPF.ViewModel
{
    public class FontViewModel : INotifyPropertyChanged
    {
        public TextControl textControl;

        public string FontFamily { get; set; }

        public int FontSize { get; set; }

        public string FontColor { get; set; }

        public string Text { get; set; }

        public event PropertyChangedEventHandler PropertyChanged = delegate (object sender, PropertyChangedEventArgs e)
        {
            
        };

    }
}
