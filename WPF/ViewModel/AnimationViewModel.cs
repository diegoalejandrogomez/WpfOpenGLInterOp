using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using SimpleEngineTileEditor;

namespace WPF.ViewModel
{
    public class AnimationViewModel : INotifyPropertyChanged
    {
        
        System.Timers.Timer aTimer;
        int index;

        public SimpleAnimatedSpriteControl AnimatedControl { get; set; }

        public AnimationViewModel()
        {
            aTimer = new System.Timers.Timer();
            aTimer.Elapsed += new ElapsedEventHandler(OnTimedEvent);
            aTimer.Enabled = true;
            index = 0;
            this.Frequency = 100;
            this.AnimatedControl = new SimpleAnimatedSpriteControl();
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

        private double frequency;
        public double Frequency
        {
            get
            {
                return frequency;
            }
            set
            {
                frequency = value;
                if (frequency == 0)
                    frequency = 1;

                aTimer.Interval = frequency;
                PropertyChanged(this, new PropertyChangedEventArgs("CurrentTile"));
            }
        }

        private String name;
        public String Name
        {
            get
            {
                return name;
            }
            set
            {
                name = value;
                PropertyChanged(this, new PropertyChangedEventArgs("Name"));
            }
        }
    }
}
