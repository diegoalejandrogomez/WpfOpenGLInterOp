#pragma once
#include "SimpleConfiguration.h"
#include "SimpleAABB.h"
#include "SimpleSpriteSheet.h"

class SIMPLE_API SimpleUtils {

public:

	inline static int NextPOT(int x)
	{
		if (x < 0)
			return 0;
		--x;
		x |= x >> 1;
		x |= x >> 2;
		x |= x >> 4;
		x |= x >> 8;
		x |= x >> 16;
		return x + 1;
	}

	
	struct AdHocBTreeNode
	{
		AdHocBTreeNode* child[2] = { nullptr,nullptr };
		SimpleAABB rc;
		SimpleTexture* texture;

		AdHocBTreeNode* Insert(const SimpleTexture* tex) {

			//If we aren't a leaf
			if (child[0] != nullptr || child[1] != nullptr) {
				//Try first child
				AdHocBTreeNode* newNode = child[0]->Insert(tex);
				if (newNode != nullptr)
					return newNode;
				//No luck with first, second is the last option
				return child[1]->Insert(tex);
			}
			else {
				//If we already have an image assigned, we fail :/
				if (texture != nullptr)
					return nullptr;
				//If the texture can't fit in the available space we fail... (we should stop failing)
				if (tex->GetWidth() > rc.size.x || tex->GetHeight() > rc.size.y)
					return nullptr;
				//If we are a perfect fit return
				if (tex->GetWidth() == rc.size.x && tex->GetHeight() == rc.size.y)
					return this;

				//Few things are a perfect fit in life, so ... split the node
				child[0] = new AdHocBTreeNode();
				child[1] = new AdHocBTreeNode();

				//Let's pick which way to split (POT is not taken into account)
				uint32_t dw = rc.size.x - tex->GetWidth();
				uint32_t dh = rc.size.y - tex->GetHeight();

				if (dw > dh) {
					child[0]->rc.position.x = rc.position.x - 0.5f* (rc.size.x - tex->GetWidth());
					child[0]->rc.position.y = rc.position.y;
					child[0]->rc.size.x = tex->GetWidth();
					child[0]->rc.size.y = rc.size.y;

					child[1]->rc.position.x = rc.position.x + 0.5f * tex->GetWidth();
					child[1]->rc.position.y = rc.position.y;
					child[1]->rc.size.x = rc.size.x - tex->GetWidth();
					child[1]->rc.size.y = rc.size.y;
				}
				else {

					child[0]->rc.position.x = rc.position.x;
					child[0]->rc.position.y = rc.position.y - 0.5f*(rc.size.y - tex->GetHeight());
					child[0]->rc.size.x = rc.size.x;
					child[0]->rc.size.y = tex->GetHeight();

					child[1]->rc.position.x = rc.position.x;
					child[1]->rc.position.y = rc.position.y + 0.5f * tex->GetHeight();
					child[1]->rc.size.x = rc.size.x;
					child[1]->rc.size.y = tex->GetHeight();

				}

				return child[0]->Insert(tex);
			}

		}
	};
	
	inline static SimpleSpriteSheet* PackTextures(std::vector<SimpleTexture*> _textures) {
	
		constexpr int initialSize = 512;
		constexpr int maxSize = 512;

		SimpleSpriteSheet* sheet = new SimpleSpriteSheet();

		int currentSize = initialSize;
		AdHocBTreeNode* root = new AdHocBTreeNode();
		bool packed = false;

		while (currentSize <= maxSize && !packed) {
			root->rc = { {0,0} , {currentSize / 2 , currentSize / 2} };
			
			packed = true;
			for (const auto t : _textures) {
			
				AdHocBTreeNode* node = root->Insert(t);
				if (node == nullptr) {
					packed = false;
					break;
				}
				else {
					node->texture = t;
					//Should create sprite frame and copy pixels
				}

			}				
			currentSize <<= 2;

		}
		
		return sheet;
	}

	


	
};