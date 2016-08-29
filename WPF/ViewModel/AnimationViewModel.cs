using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;

namespace WPF.ViewModel
{
    public class AnimationViewModel : INotifyPropertyChanged
    {
        System.Timers.Timer aTimer;
        int index;

        public AnimationViewModel()
        {
            aTimer = new System.Timers.Timer();
            aTimer.Elapsed += new ElapsedEventHandler(OnTimedEvent);
            aTimer.Interval = 100;
            aTimer.Enabled = true;
            index = 0;
        }

        private void OnTimedEvent(object source, ElapsedEventArgs e)
        {
            index++;
            if(index >= Tiles.Count)
            {
                index = 0;
            }

            this.CurrentTile = Tiles.ElementAt(index);
        }

        public List<TileViewModel> Tiles;

        private TileViewModel currentTile;

        public event PropertyChangedEventHandler PropertyChanged = delegate (object sender, PropertyChangedEventArgs e)
        {

        };

        public TileViewModel CurrentTile
        {
            get
            {
                return currentTile;
            }
            set
            {
                currentTile = value;
                PropertyChanged(this, new PropertyChangedEventArgs("CurrentTile"));
            }
        }
    }
}
