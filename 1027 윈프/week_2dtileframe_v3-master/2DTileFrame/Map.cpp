#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <string>
#include "Sprite.h"
#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::Init(LPDIRECT3DDEVICE9 dxDevice, ID3DXSprite* spriteDX)
{
	// 맵용 스프라이트 리스트 작업.
	// 타일 갯수하고 개별 타일 크기 합의 완료 (32x32, 256)
	int srcX = 0;
	int srcY = 0;
	int tileSize = 32;
	LPCWSTR fileName = L"C:/Users/Atents/Desktop/1027 윈프/week_2dtileframe_v3-master/Resources/Images/PathAndObjects.png";
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			Sprite* sprite = new Sprite();
			sprite->Init(fileName,
				srcX, srcY, tileSize, tileSize, 1.0f,
				dxDevice, spriteDX);
			_spriteList.push_back(sprite);

			srcX += tileSize;
		}

		srcX = 0;
		srcY += tileSize;
	}

	// 맵 생성
	int tileMapIndex[16][16];
	//스크립트 대체
	/*
	int idx = 0;
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			//tileMapIndex[y][x] = idx++;
			tileMapIndex[y][x] = 17;
		}
	}
	*/
	{
		std::string fileName = "map.csv";
		std::vector<std::string> recordList;
		std::ifstream infile(fileName);
		if (true == infile.is_open()) //파일이 정상적으로 열렸으면
		{
			char recordString[1000];
			while (false == infile.eof()) //파일이 끝날때까지 순환
			{
				//한줄씩 읽어서 리스트에 저장
				infile.getline(recordString, 1000);
				recordList.push_back(recordString);
			}
		}

		//레코드를 토큰으로 분리해서 게임에 적용
		char record[1000];
		for (int y = 0; y < 16; y++)
		{
			// 한줄 record에 복사
			strcpy(record, recordList[y].c_str());
			char* token = strtok(record, ",");
			for (int x = 0; x < 16; x++)
			{
				int tileIndex = atoi(token);
				tileMapIndex[y][x] = tileIndex;
				token = strtok(NULL, ",");
			}
		}
	}

	// 스프라이트를  생성
	//LPCWSTR fileName = L"C:/Users/Atents/Desktop/1027 윈프/week_2dtileframe_v3-master/Resources/Images/PathAndObjects.png";
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			int spriteIndex = tileMapIndex[y][x];
			_tileSprite[y][x] = _spriteList[spriteIndex];
			/*
			_tileSprite[y][x] = new Sprite();
			LPCWSTR scriptName = L"Test.json";

			int index = tileMapIndex[y][x];
			switch (index)
			{
			case 0:
				scriptName = L"PlayerLeft.json";
				break;
			case 1:
				scriptName = L"PlayerRight.json";
				break;
			case 2:
				scriptName = L"PlayerUp.json";
				break;
			case 3:
				scriptName = L"PlayerDown.json";
				break;
			}

			_tileSprite[y][x]->Init(fileName, scriptName, dxDevice, spriteDX);
			*/
		}
	}
}

void Map::Update(float deltaTime)
{
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			_tileSprite[y][x]->Update(deltaTime);
		}
	}
}

void Map::Render()
{
	float startX = 0.0f;
	float startY = 0.0f;
	float posX = startX;
	float posY = startY;
	int tileSize = 32;
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			_tileSprite[y][x]->SetPosition(posX + 30, posY + 30);
			_tileSprite[y][x]->Render();
			posX += (tileSize);
		}
		posX = startX;
		posY += (tileSize);
	}
}

void Map::Release()
{
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			_tileSprite[y][x]->Release();
		}
	}
}

void Map::Reset()
{
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			_tileSprite[y][x]->Reset();
		}
	}
}

void Map::Deinit()
{
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			if (NULL != _tileSprite[y][x])
			{
				delete _tileSprite[y][x];
			}
		}
	}
}
