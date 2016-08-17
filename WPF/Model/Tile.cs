using System.Collections;
using System.Collections.Generic;

namespace WPF.Model
{
    public class Tile
    {
        public Tile()
        {
            Properties = new List<ResourceProperty>();
        }

        public List<ResourceProperty> Properties { get; set; }
    }
}