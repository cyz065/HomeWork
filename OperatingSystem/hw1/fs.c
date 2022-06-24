#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disk.h"
#include "fs.h"

void SetInodeBytemap(int inodeno)
{
	// (1) block size memory allocation
	char* buf = (char*)malloc(BLOCK_SIZE);

	// (2, 3) Read data from Inode ByteMap
	DevReadBlock(INODE_BYTEMAP_BLOCK_NUM, buf);

	// (4) set inode 1
	*(buf + inodeno) = 1;

	// (5) store block to disk
	DevWriteBlock(INODE_BYTEMAP_BLOCK_NUM, buf);
	free(buf);
}


void ResetInodeBytemap(int inodeno)
{
	// (1) block size memory allocation
	char* buf = (char *)malloc(BLOCK_SIZE);
	
	// (2, 3) Read data from Inode ByteMap
	DevReadBlock(INODE_BYTEMAP_BLOCK_NUM, buf);

	// (4) set 0 to inodeno
	*(buf + inodeno) = 0;

	// (5) store block to disk
	DevWriteBlock(INODE_BYTEMAP_BLOCK_NUM, buf);
	free(buf);
}

void SetBlockBytemap(int blkno)
{
	// (1) block size memory allocation
	char* buf = (char*)malloc(BLOCK_SIZE);
	
	// (2, 3) Read data from block byte map	
	DevReadBlock(BLOCK_BYTEMAP_BLOCK_NUM, buf);

	// (4) set blkno 1
	*(buf + blkno) = 1;
	
	// (5) store block to disk
	DevWriteBlock(BLOCK_BYTEMAP_BLOCK_NUM, buf);
	free(buf);
}


void ResetBlockBytemap(int blkno)
{
	// (1) block size memory allocation
	char* buf = (char*)malloc(BLOCK_SIZE);

	// (2, 3) Read data from blkno
	DevReadBlock(BLOCK_BYTEMAP_BLOCK_NUM, buf);

	// (4) set blkno 0
	*(buf + blkno) = 0;

	// (5) store block to disk
	DevWriteBlock(BLOCK_BYTEMAP_BLOCK_NUM, buf);
	free(buf);
}


void PutInode(int inodeno, Inode* pInode)
{	
	// (1) block size memory allocation
	char* buf = (char*)malloc(BLOCK_SIZE);

	// (2) get block number
	int block_num = (inodeno / 16) + INODELIST_BLOCK_FIRST;

	// (3, 4) read data from block_num
	DevReadBlock(block_num, buf);
	
	// (5) copy inode to inode block's inode index
	int inode_idx = inodeno % 16;
	memcpy(buf + (inode_idx * sizeof(Inode)), pInode, sizeof(Inode));

	// (6) store block to disk
	DevWriteBlock(block_num, buf);
	free(buf);
}


void GetInode(int inodeno, Inode* pInode) {

	// (1) block size memory allocation
	char* buf = (char*)malloc(BLOCK_SIZE);

	// (2) get inode's block number	
	int block_num = (inodeno / 16) + INODELIST_BLOCK_FIRST;
	
	// (3, 4) read block number from disk
	DevReadBlock(block_num, buf);
	
	// (5) copy block number's inode index to pInode
	int inode_idx = inodeno % 16;
	memcpy(pInode, buf + inode_idx * sizeof(Inode), sizeof(Inode));
	free(buf);
}


int GetFreeInodeNum(void)
{	
	// (1) block size memory allocation
	char* buf = (char*)malloc(BLOCK_SIZE);

	/// (2) read block from disk
	DevReadBlock(INODE_BYTEMAP_BLOCK_NUM, buf);

	// (3) frst fit search 0
	for(int i = 0; i < 64; i++) {
		if(*(buf + i) == 0) {
			free(buf);
			return i;
		}
	}
}


int GetFreeBlockNum(void)
{
	// (1) block size memory allocation
	char* buf = (char*)malloc(BLOCK_SIZE);
	
	// (2) read block from disk
	DevReadBlock(BLOCK_BYTEMAP_BLOCK_NUM, buf);
	
	// (3) first fit search 0
	for(int i = 0; i < BLOCK_SIZE; i++) {
		if(buf[i] == 0) {
			free(buf);
			return i;
		}
	}
}

void PutIndirectBlockEntry(int blkno, int index, int number)
{
	// (1) block size memory alloc
	char* buf = (char*)malloc(BLOCK_SIZE);

	// (2) read block from disk
	DevReadBlock(blkno, buf);

	// (3) get index address and store number to index
	int* cursor = ((int *)buf + index);
	*cursor = number;
	
	// (4) store block to disk
	DevWriteBlock(blkno, buf);
	free(buf);
}

int GetIndirectBlockEntry(int blkno, int index)
{
	// (1) block size memory allocation
	char* buf = (char*)malloc(BLOCK_SIZE);

	// (2) read block from disk
	DevReadBlock(blkno, buf);
	
	// (3) get index address and get number from entry
	int* cursor = ((int*)buf + index);
	int value = *cursor;
	free(buf);
	return value;
}

void PutDirEntry(int blkno, int index, DirEntry* pEntry)
{
	// (1) block size memory allocation
	char* buf = (char*)malloc(BLOCK_SIZE);

	// (2) read block
	DevReadBlock(blkno, buf);
	
	// (3) store pEntry to index entry by copy
	DirEntry* cursor = ((DirEntry *)buf + index);
	memcpy(cursor, pEntry, sizeof(DirEntry));

	// (4) store block to disk	
	DevWriteBlock(blkno, buf);
	free(buf);
}

int GetDirEntry(int blkno, int index, DirEntry* pEntry)
{
	// (1) block size memory allocation
	char* buf = (char*)malloc(BLOCK_SIZE);

	// (2) read block from disk
	DevReadBlock(blkno, buf);

	// (3) get index address and copy entry to pEntry
	DirEntry* cursor = ((DirEntry *)buf + index);
	memcpy(pEntry, cursor, sizeof(DirEntry));
	
	// (4) check entry is Valid or not
	if((cursor->inodeNum) != INVALID_ENTRY) {
		free(buf);
		return 1;
	}
	else {
		free(buf);
		return -1;	
	}
}

void FileSysInit(void)
{
	DevCreateDisk();
	DevOpenDisk();

	// set 0 to block
	char* buf = (char*)malloc(BLOCK_SIZE);
	memset(buf, 0, BLOCK_SIZE);
	
	// initialize SuperBlock, InodeBytemap, BlockBytemap, Inodelist
	for(int i = 0; i < 7; i++) 
		DevWriteBlock(i, buf);
	free(buf);
}

void RemoveDirEntry(int blkno, int index) {
	// (1) block size memory allocation
	char* buf = (char *)malloc(BLOCK_SIZE);

	// (2) read data from disk
	DevReadBlock(blkno, buf);

	// (3) get directory entry address and set INVALID_ENTRY to inodeNum
	DirEntry* cursor = ((DirEntry *)buf + index);
	cursor->inodeNum = INVALID_ENTRY;
	
	// (4) store block to disk
	DevWriteBlock(blkno, buf);
	free(buf);
}

void RemoveIndirectBlockEntry(int blkno, int index) {
	// (1) block size memory allocation
	char* buf = (char*)malloc(BLOCK_SIZE);

	// (2) read data from disk
	DevReadBlock(blkno, buf);

	// (3) get index entry address and set INVALID_ENTRY to entry
	int* cursor = ((int *)buf + index);
	*cursor = INVALID_ENTRY;

	// (4) store block to disk
	DevWriteBlock(blkno, buf);
	free(buf);
}
