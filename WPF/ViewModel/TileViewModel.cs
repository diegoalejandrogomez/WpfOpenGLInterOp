using SimpleEngineControls;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;

namespace WPF.ViewModel
{
    public class TileViewModel
    {
        public BitmapImage Image { get; set; }

        public String Path { get; set; }

        public SpriteSheetControl SpriteControl { get; set; }

        public int x { get; set; }

        public int y { get; set; }

        public int width { get; set; }

        public int heigth { get; set; }

        public bool Splited { get; set; }

        public int Idx { get; set; }
    }
}
