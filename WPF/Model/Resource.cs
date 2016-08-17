using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPF.Model
{
    public class Resource
    {
        public Resource()
        {
            this.Properties = new List<ResourceProperty>();
        }

        public byte[] Data { get; set; }

        public String Name { get; set; }

        public List<ResourceProperty> Properties { get; set; }
    }
}
