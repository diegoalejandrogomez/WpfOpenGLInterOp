using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace SimpleEngineTileEditor
{
    class SimpleEngine
    {

        #region DllImports
        [DllImport("SimpleEngine_dyn.dll")]
        static extern IntPtr SimpleEngine_Instance();

        #endregion

        public SimpleEngine GetInstance()
        {
            if (_instance == null)
            {
                _instance = new SimpleEngine();
                _nativeInstance = SimpleEngine_Instance();
            }

            return _instance;
        }

                
        static SimpleEngine _instance;
        IntPtr _nativeInstance = IntPtr.Zero;
    }
}
