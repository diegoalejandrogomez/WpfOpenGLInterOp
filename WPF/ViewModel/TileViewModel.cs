using SimpleEngineTileEditor;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;

namespace WPF.ViewModel
{
    public class TileViewModel : IDisposable
    {
        public Guid DateTimeToGuid()
        {
            DateTime dateTime = DateTime.Now;
            Guid guid = Guid.NewGuid();
            string guidEnd = guid.ToString().Substring(guid.ToString().IndexOf("-"), guid.ToString().Length - guid.ToString().IndexOf("-"));
            string guidStart = dateTime.Day.ToString() + dateTime.Month.ToString() + dateTime.Year.ToString();
            guidStart = guidStart.PadRight(8, '0');
            guid = new Guid(guidStart + guidEnd);

            return guid;
        }

        public TileViewModel()
        {
            this.Id = DateTimeToGuid();

        }

        public TileViewModel(Guid Id)
        {
            this.Id = Id;
        }

        public readonly Guid Id;

        public BitmapImage Image { get; set; }

        public String Path { get; set; }

        public SpriteSheetControl SpriteControl { get; set; }

        public int x { get; set; }

        public int y { get; set; }

        public int width { get; set; }

        public int heigth { get; set; }

        public bool Splited { get; set; }

        public int Idx { get; set; }

        public void Dispose()
        {
            Image = null;
        }
    }
}
