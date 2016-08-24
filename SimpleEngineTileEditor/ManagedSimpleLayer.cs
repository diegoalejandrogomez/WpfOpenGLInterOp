using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace SimpleEngineTileEditor
{
    public class ManagedSimpleLayer
    {
        #region DllImports
        //Managed simple object imports
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern IntPtr SimpleLayer_Create();

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void SimpleLayer_Destroy(IntPtr sLayer);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleLayer_AddEntity(IntPtr sLayer, IntPtr sObj);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern bool SimpleLayer_RemoveEntity(IntPtr sLayer, IntPtr sObj);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleLayer_Clear(IntPtr sLayer, bool deleteEntities = false);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleLayer_SetZ(IntPtr sLayer, float Z);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern float SimpleLayer_GetZ(IntPtr sLayer);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern UInt32 SimpleLayer_GetName(IntPtr sLayer);
        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern IntPtr SimpleLayer_GetStringName(IntPtr sLayer);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleLayer_SetName(IntPtr sLayer, String name);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern void SimpleLayer_SetQueryable(IntPtr sLayer, bool value);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern bool SimpleLayer_IsQueryable(IntPtr sLayer);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern String SimpleLayer_Serialize(IntPtr sLayer);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern bool SimpleLayer_Deserialize(IntPtr sLayer, String layer);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern IntPtr SimpleLayer_EntitiesBegin(IntPtr layer);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern IntPtr SimpleLayer_EntitiesNext(IntPtr layer);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl )]
        static extern IntPtr SimpleLayer_EntitiesEnd(IntPtr layer);

        [DllImport("SimpleEngine_dyn.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern IntPtr SimpleScene_AddLayer(IntPtr layer);
        #endregion
        IntPtr sLayer;

        public void Remove()
        {
        }

        public ManagedSimpleLayer()
        {          
            sLayer = SimpleLayer_Create();
            //Add the layer to the current scene
            SimpleScene_AddLayer(sLayer);
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
                return Marshal.PtrToStringAnsi(SimpleLayer_GetStringName(sLayer));             
            }
            set
            {
                SimpleLayer_SetName(sLayer, value);
            }
        }

        public List<ManagedSimpleObject> SimpleObjects
        {
            get
            {
                List<ManagedSimpleObject> managedSimpleObjects = new List<ManagedSimpleObject>();
                SimpleLayer_EntitiesBegin(sLayer);
                while(true)
                {
                    var entity = SimpleLayer_EntitiesNext(sLayer);
                    if(entity == null)
                    {
                        break;
                    }

                    ManagedSimpleObject simpleObject = new ManagedSimpleObject();
                    simpleObject.SetSimpleObject(entity);
                    managedSimpleObjects.Add(simpleObject);
                }

                return managedSimpleObjects;
            }
        }
    }
    
}