using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace SimpleEngineTileEditor
{
    class SpriteSheetControl
    {
        #region SimpleSpriteSheetRendererImports
        [DllImport("SimpleEngine_dyn.dll")]
        static extern IntPtr SimpleSpriteSheetRenderer_Create();
        [DllImport("SimpleEngine_dyn.dll")]
        static extern IntPtr SimpleSpriteSheetRenderer_Destroy(IntPtr sprite);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern IntPtr SimpleRenderer_GetSpriteSheet(String texturePath);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern bool SimpleRenderer_CreateSpriteSheet(String texturePath, int frameSizeX, int frameSizeY, int frameCountX, int frameCountY);
        [DllImport("SimpleEngine_dyn.dll")]
        static extern bool SimpleRenderer_CreateSpriteSheetEmpty(String texturePath);


        #endregion
        IntPtr _simpleSpriteSheetRenderer;
        ManagedSimpleObject _managedSimpleObject;

        public ManagedSimpleObject GetManagedSimpleObject() {

            return _managedSimpleObject;

        }
        public SpriteSheetControl() {
            _managedSimpleObject = new ManagedSimpleObject();
            _simpleSpriteSheetRenderer = SimpleSpriteSheetRenderer_Create();

        }
        ~SpriteSheetControl() {
            SimpleSpriteSheetRenderer_Destroy(_simpleSpriteSheetRenderer);
        }
        int AddControl(String path, int x, int y, int w, int h){

            //remove temp
            int from = path.IndexOf("/temp/");
            path.Remove(0, from + 6);

            //Try to find spritesheet to use
            IntPtr spriteSheet = SimpleRenderer_GetSpriteSheet(path);

            if (spriteSheet == IntPtr.Zero) {

                SimpleRenderer_CreateSpriteSheetEmpty(path);
                spriteSheet = SimpleRenderer_GetSpriteSheet(path);
            }

            int idx = 0;

             return idx;
        }

   //     property float positionX
   //     {

   //         float get()
   //     {
   //         if (this->_simpleSpriteSheetRenderer == nullptr)
   //             return 0;
   //         return _simpleSpriteSheetRenderer->GetPosition().x;
   //     }

   //     void set(float position)
   //     {
   //         _simpleSpriteSheetRenderer->SetPosition(glm::vec3(position, _simpleSpriteSheetRenderer->GetPosition().y, _simpleSpriteSheetRenderer->GetPosition().z));
   //     }
   // };

   // property float positionY
   // {
			//float get() {
   //         if (this->_simpleSpriteSheetRenderer == nullptr)
   //             return 0;
   //         return _simpleSpriteSheetRenderer->GetPosition().y;
   //     }

   //     void set(float position)
			//{
   //         _simpleSpriteSheetRenderer->SetPosition(glm::vec3(_simpleSpriteSheetRenderer->GetPosition().x, position, _simpleSpriteSheetRenderer->GetPosition().z));
   //     }
   //     };

   //     property float heigth
   //     {
   //         float get() {
   //             if (this->_simpleSpriteSheetRenderer == nullptr)
   //                 return 0;
   //             return _simpleSpriteSheetRenderer->GetSize().y;
   //         }

   //         void set(float heigth)
			//{
   //             _simpleSpriteSheetRenderer->SetSize(glm::vec2(_simpleSpriteSheetRenderer->GetSize().x, heigth));
   //         }
   //     };

   //     property float width
   //     {
   //         float get() {
   //             if (this->_simpleSpriteSheetRenderer == nullptr)
   //                 return 0;
   //             return _simpleSpriteSheetRenderer->GetSize().x;
   //         }

   //         void set(float width)
			//{
   //             _simpleSpriteSheetRenderer->SetSize(glm::vec2(width, _simpleSpriteSheetRenderer->GetSize().y));
   //         }
   //     };



    }
}
