using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPF.Model
{
    public class Resource
    {
        public byte[] Data { get; set; }

        public String Name { get; set; }

        public ResourceProperty Properties { get; set; }
    }
}
