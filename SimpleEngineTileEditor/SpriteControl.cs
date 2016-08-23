using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace SimpleEngineTileEditor
{
    class SpriteControl
    {

        #region SimpleSpriteRendererImports
        [DllImport("SimpleEngine_dyn.dll")]
        static extern IntPtr SimpleSpriteRenderer_Create();
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleSpriteRenderer_Destroy(IntPtr sprite);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleSpriteRenderer_SetAsTexture(IntPtr sprite, String name);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern void SimpleScene_AddEntityWithIdx(IntPtr sObj, int nLayer);

        #endregion


        IntPtr _simpleSpriteRenderer;
        
        ManagedSimpleObject _managedSimpleObject;

        public ManagedSimpleObject GetManagedSimpleObject() {
            return _managedSimpleObject;
        }

        public SpriteControl() {

            _simpleSpriteRenderer = SimpleSpriteRenderer_Create();
            _managedSimpleObject = new ManagedSimpleObject();
            _managedSimpleObject.SetSimpleObject(_simpleSpriteRenderer);            
        }

        ~SpriteControl() {
            SimpleSpriteRenderer_Destroy(_simpleSpriteRenderer);
        }
        public void AddControl(String path) {

            SimpleSpriteRenderer_SetAsTexture(_simpleSpriteRenderer, path);
            //Add entity to layer 0
            SimpleScene_AddEntityWithIdx(_simpleSpriteRenderer, 0);

        }

    }
}
