using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace SimpleEngineTileEditor
{
    class ManagedSimpleLayer
    {
        #region DllImports
        //Managed simple object imports
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleLayer_AddEntity(IntPtr sLayer, IntPtr sObj);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern bool SimpleLayer_RemoveEntity(IntPtr sLayer, IntPtr sObj);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleLayer_Clear(IntPtr sLayer, bool deleteEntities = false);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleLayer_SetZ(IntPtr sLayer, float Z);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern float SimpleLayer_GetZ(IntPtr sLayer);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern String SimpleLayer_GetName(IntPtr sLayer);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleLayer_SetName(IntPtr sLayer, String name);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleLayer_SetQueryable(IntPtr sLayer, bool value);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern bool SimpleLayer_IsQueryable(IntPtr sLayer);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern String SimpleLayer_Serialize(IntPtr sLayer);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern bool SimpleLayer_Deserialize(IntPtr sLayer, String layer);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern IntPtr SimpleLayer_EntitiesBegin(IntPtr layer);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern IntPtr SimpleLayer_EntitiesNext(IntPtr layer);

        [DllImport("SimpleEngine_dyn.dll")]
        static extern IntPtr SimpleLayer_EntitiesEnd(IntPtr layer);
        #endregion
        IntPtr sLayer;

        public void Remove()
        {
        }

        public ManagedSimpleLayer(IntPtr simpleLayer)
        {
            sLayer = simpleLayer;
        }

        public float Z
        {
            get
            {
                return SimpleLayer_GetZ(sLayer);
            }
            set
            {
                SimpleLayer_SetZ(sLayer, value);
            }
        }

        public String Name
        {
            get
            {
                return SimpleLayer_GetName(sLayer);
            }
            set
            {
                SimpleLayer_SetName(sLayer, value);
            }
        }

        /*public List<ManagedSimpleObject> SimpleObjects
        {
            get
            {
                return SimpleLayer_GetSimpleObjects(sLayer)
            }

            set
            {
                SimpleLayer_SetSimpleObjects(sLayer, value);
            }
        }*/
    }
    
}