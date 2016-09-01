#pragma once
#include "SimpleConfiguration.h"
#include "SimpleTextureRegion.h"
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
		SimpleTextureRegion rc;
		SimpleTexture* texture;

		AdHocBTreeNode* Insert(const SimpleTextureRegion& tex) {

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
				if (tex.Width() > rc.Width() || tex.Height() > rc.Height())
					return nullptr;
				//If we are a perfect fit return
				if (tex.Width() == rc.Width() && tex.Height() == rc.Height())
					return this;

				//Few things are a perfect fit in life, so ... split the node
				child[0] = new AdHocBTreeNode();
				child[1] = new AdHocBTreeNode();

				//Let's pick which way to split (POT is not taken into account)
				uint32_t dw = (uint32_t)rc.Width() - tex.Width();
				uint32_t dh = (uint32_t)rc.Height() - tex.Height();

				if (dw > dh) {

					child[0]->rc.lowerLeft.x = rc.lowerLeft.x;
					child[0]->rc.lowerLeft.y = rc.lowerLeft.y;
					child[0]->rc.upperRight.x = rc.lowerLeft.x + tex.Width() - 1;
					child[0]->rc.upperRight.y = rc.upperRight.y;
					
					child[1]->rc.lowerLeft.x = rc.lowerLeft.x + tex.Width();
					child[1]->rc.lowerLeft.y = rc.lowerLeft.y;
					child[1]->rc.upperRight.x = rc.upperRight.x;
					child[1]->rc.upperRight.y = rc.upperRight.y;

				}
				else {

					child[0]->rc.lowerLeft.x = rc.lowerLeft.x;
					child[0]->rc.lowerLeft.y = rc.lowerLeft.y;
					child[0]->rc.upperRight.x = rc.upperRight.x;
					child[0]->rc.upperRight.y = rc.lowerLeft.y + tex.Height() -1;

					child[1]->rc.lowerLeft.x = rc.lowerLeft.x;
					child[1]->rc.lowerLeft.y = rc.lowerLeft.y + tex.Height();
					child[1]->rc.upperRight.x = rc.upperRight.x;
					child[1]->rc.upperRight.y = rc.upperRight.y;

				}

				return child[0]->Insert(tex);
			}

		}
	};
	
	inline static SimpleSpriteSheet* PackTextures(std::vector<SimpleTexture*> _textures, uint32_t padding) {
	
		constexpr int initialSize = 512;
		constexpr int maxSize = 4096;

		int currentSize = initialSize;
		AdHocBTreeNode* root = new AdHocBTreeNode();
		bool packed = false;
		SimpleSpriteSheet* sheet;
		while (currentSize <= maxSize && !packed) {
			root->rc.lowerLeft = { 0 , 0};
			root->rc.upperRight= { currentSize,currentSize};
			
			sheet = new SimpleSpriteSheet();
			sheet->LoadTextureFromMemory(nullptr, 1, currentSize, currentSize, false);
			packed = true;
			for (const auto t : _textures) {
				
				SimpleTextureRegion toInsert;
				toInsert.lowerLeft = { 0,0 };
				toInsert.upperRight= { t->GetWidth() - 1 + 2 * padding, t->GetHeight() - 1 + 2 * padding};

				AdHocBTreeNode* node = root->Insert(toInsert);
				if (node == nullptr) {
					packed = false;
					delete sheet;
					sheet = nullptr;
					break;
				}
				else {
					node->texture = t;
					node->rc.lowerLeft.x += padding;
					node->rc.upperRight.x -= padding;
					node->rc.lowerLeft.y += padding;
					node->rc.upperRight.y -= padding;
					sheet->SetSubTexture(node->rc, t);
					sheet->AddSpriteFrame(node->rc.lowerLeft, {node->rc.Width(), node->rc.Height()},false);
				}

			}				
			currentSize <<= 2;

		}
		
		SIMPLE_ASSERT(sheet != nullptr);
		
		sheet->Flush();
		return sheet;
	}

	


	
};