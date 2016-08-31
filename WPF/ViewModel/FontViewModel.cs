using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPF.ViewModel
{
    public class FontViewModel : INotifyPropertyChanged
    {
        public string FontFamily { get; set; }

        public string FontSize { get; set; }

        public string FontColor { get; set; }

        public event PropertyChangedEventHandler PropertyChanged = delegate (object sender, PropertyChangedEventArgs e)
        {
            
        };

    }
}
