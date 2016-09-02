using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPF.Model
{
    public class Animation
    {
        public Animation()
        {
            this.Resources = new List<Guid>();
        }

        public string Name { get; set; }

        public double Frequency { get; set; }

        public List<Guid> Resources { get; set; }
    }
}
