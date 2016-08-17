using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPF.Model
{
    public class Project
    {
        public Project()
        {
            Resources = new List<Resource>();
            Scenes = new List<Scene>();
        }

        public List<Resource> Resources { get; set; }

        public List<Scene> Scenes { get; set; }
    }
}
