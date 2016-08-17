using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPF.Model
{
    public class Scene
    {
        public Scene()
        {
            Tiles = new List<Tile>();
        }

        public List<Tile> Tiles { get; set; }
    }
}
