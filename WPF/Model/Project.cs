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
            Scenes = new List<String>();
            Animations = new List<Model.Animation>();
        }

        public List<Resource> Resources { get; set; }

        public List<String> Scenes { get; set; }

        public List<Animation> Animations { get; set; }
    }
}
