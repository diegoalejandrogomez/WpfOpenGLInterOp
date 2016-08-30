using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using SimpleEngineTileEditor;
using System.Windows;
using System.Windows.Threading;

namespace WPF.ViewModel
{
    public class AnimationViewModel : INotifyPropertyChanged
    {
        
        private DispatcherTimer aTimer;
        private int index;
        private TileViewModel currentTile;
        private double frequency;
        private String name;

        public AnimationViewModel()
        {
            aTimer = new DispatcherTimer(System.Windows.Threading.DispatcherPriority.Render);
            aTimer.Tick += new EventHandler(OnTimedEvent);
            index = 0;
            this.Frequency = 100;
            aTimer.Start();
            AnimatedControl = new SimpleAnimatedSpriteControl();
        }

        private void OnTimedEvent(object sender, EventArgs e)
        {
            if (Tiles != null)
            {
                index++;
                if (index >= Tiles.Count)
                {
                    index = 0;
                }

                this.CurrentTile = Tiles.ElementAt(index);
            }
        }

        public List<TileViewModel> Tiles;

        public SimpleAnimatedSpriteControl AnimatedControl { get; set; }

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

                aTimer.Interval = new TimeSpan((long)frequency * 10000);
                PropertyChanged(this, new PropertyChangedEventArgs("CurrentTile"));
            }
        }

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

        public event PropertyChangedEventHandler PropertyChanged = delegate (object sender, PropertyChangedEventArgs e)
        {

        };

        public void Validate()
        {
            if (String.IsNullOrEmpty(this.Name))
            {
                throw new Exception("Please enter a name for this animation");
            }
        }
    }
}
