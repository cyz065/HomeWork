#include <stdio.h>
#include <stdlib.h>
#include "disk.h"
#include "hw1.h"
#include "hw2.h"
#include <string.h>

FileDescTable* pFileDescTable;
FileTable* pFileTable;
DirEntry* pCursor = NULL;

int block_index = 0;
int idx = 0;
int indirBlock_index = 0;
int cursor_index = 0;
int idx2 = 0;

int find_path(int i, int idx, char** path_arr, Inode* inode, char* cursor) 
{
	DirEntry* tmp = (DirEntry*)malloc(sizeof(DirEntry));
	int return_block = inode->dirBlockPtr[0];

	if(*path_arr == NULL) 
		return return_block;
	
	else if(i == idx - 1)
		return return_block;

	for(int j = 0; j < NUM_OF_DIRENT_PER_BLK; j++) {
		if(GetDirEntry(inode->dirBlockPtr[0], j, tmp) == 1) {
			if(strcmp(path_arr[i], tmp->name) == 0) {
				Inode* tmp_node = (Inode*)malloc(sizeof(Inode));
				GetInode(tmp->inodeNum, tmp_node);

				char* tmp_buf = (char*)malloc(BLOCK_SIZE);
				DevReadBlock(tmp_node->dirBlockPtr[0], tmp_buf);
				return find_path(i + 1, idx, path_arr, tmp_node, tmp_buf);
			}
		}	
	}
	return -1;
}


int OpenFile(const char* name, OpenFlag flag)
{
	int free_inode = GetFreeInodeNum();
	int fd;
	int sub_block;

	Inode* pInode = (Inode*)malloc(sizeof(Inode));
	char* buf = (char*)malloc(BLOCK_SIZE);
	FileSysInfo* fileSysInfo = (FileSysInfo*)malloc(sizeof(FileSysInfo));
	File* file = malloc(sizeof(File));

	GetInode(0, pInode);
	DevReadBlock(pInode->dirBlockPtr[0], buf);

	DirEntry* cursor = (DirEntry*)malloc(sizeof(DirEntry));
	DescEntry* desc_entry = (DescEntry*)malloc(sizeof(DescEntry));

	char file_name[MAX_NAME_LEN];
	strcpy(file_name, name);

	char* tmp = strtok(file_name, "/");
	int idx = 0;
	char* file_arr[MAX_NAME_LEN];
	int i = 0;

	while(tmp != NULL) {
		*(file_arr + idx) = tmp;
		idx++;
		tmp = strtok(NULL, "/");
	}

	if(flag == OPEN_FLAG_CREATE) 
	{
		int path_block = find_path(i, idx, file_arr, pInode, buf);
		if(path_block == -1) {
			return -1;
		}

		Inode* parent = (Inode*)malloc(sizeof(Inode));
		GetDirEntry(path_block, 0, cursor);
		int parent_inode = cursor->inodeNum;
		GetInode(parent_inode, parent);

		for(int i = 0; i < NUM_OF_DIRENT_PER_BLK; i++) {
			if(GetDirEntry(path_block, i, cursor) == 1) {
				if(strcmp(cursor->name, file_arr[idx - 1]) == 0) {
					
					for(int i = 0; i < DESC_ENTRY_NUM; i++) {
						if(pFileDescTable->pEntry[i].bUsed == 0) {
							pFileDescTable->pEntry[i].bUsed = 1;
							fd = i;
							file->inodeNum = cursor->inodeNum;
							file->bUsed = 1;
							//file->fileOffset = 0;
							for(int j = 0; j < MAX_FILE_NUM; j++) {
								if(pFileTable->pFile[j].bUsed == 0) {
									pFileTable->pFile[j] = *file;
									pFileTable->pFile[j].bUsed = 1;
									pFileDescTable->pEntry[i].fileTableIndex = j;
									pFileTable->numUsedFile += 1;
									pFileDescTable->numUsedDescEntry += 1;
									return fd;
								}
							}
						}
					}		
				}
				else if(i < 8 && strcmp(cursor->name, "") == 0) {
					strcpy(cursor->name, file_arr[idx - 1]);
					cursor->inodeNum = free_inode;
					PutDirEntry(path_block, i, cursor);

					GetInode(free_inode, pInode);
					pInode->type = FILE_TYPE_FILE;
					pInode->size = 0;
					PutInode(free_inode, pInode);

					SetInodeBytemap(free_inode);

					DevReadBlock(0, buf);
					fileSysInfo = (FileSysInfo*)buf;
					fileSysInfo->numAllocInodes += 1;
					DevWriteBlock(0, buf);

					for(int i = 0; i < DESC_ENTRY_NUM; i++) {
                        if(pFileDescTable->pEntry[i].bUsed == 0) {
                            pFileDescTable->pEntry[i].bUsed = 1;
                            fd = i;
							
							file->inodeNum = free_inode;
							file->fileOffset = 0;
							file->bUsed = 1;
							for(int j = 0; j < MAX_FILE_NUM; j++) {
								if(pFileTable->pFile[j].bUsed == 0) {
									pFileTable->pFile[j] = *file;
									pFileTable->pFile[j].bUsed = 1;
									pFileDescTable->pEntry[i].fileTableIndex = j;
									pFileTable->numUsedFile += 1;
									pFileDescTable->numUsedDescEntry += 1;
									return fd;
								}
							}
                        }
                    }
				}
			}
		}

		for(int i = 8; i < NUM_OF_DIRENT_PER_BLK * NUM_OF_DIRECT_BLOCK_PTR; i++) {
			if(parent->dirBlockPtr[i / NUM_OF_DIRENT_PER_BLK] == 0) {
				sub_block = GetFreeBlockNum();
				parent->dirBlockPtr[i / NUM_OF_DIRENT_PER_BLK] = sub_block;
				parent->allocBlocks += 1;
				PutInode(parent_inode, parent);
				SetBlockBytemap(sub_block);

				DevReadBlock(0, buf);
				fileSysInfo = (FileSysInfo*)buf;
				fileSysInfo->numAllocBlocks += 1;
				fileSysInfo->numFreeBlocks -= 1;
				DevWriteBlock(0, buf);
			}
			if(GetDirEntry(parent->dirBlockPtr[i / NUM_OF_DIRENT_PER_BLK], i % NUM_OF_DIRENT_PER_BLK, cursor) == 1) {
				if(strcmp(cursor->name, file_arr[idx - 1]) == 0) {
					for(int i = 0; i < DESC_ENTRY_NUM; i++) {
						if(pFileDescTable->pEntry[i].bUsed == 0) {
							pFileDescTable->pEntry[i].bUsed = 1;
							fd = i;
							file->inodeNum = cursor->inodeNum;
							//file->fileOffset = 0;
							file->bUsed = 1;
							for(int j = 0; j < MAX_FILE_NUM; j++) {
								if(pFileTable->pFile[j].bUsed == 0){
									pFileTable->pFile[j] = *file;
									pFileTable->pFile[j].bUsed = 1;
									pFileDescTable->pEntry[i].fileTableIndex = j;
									pFileDescTable->numUsedDescEntry += 1;
									pFileTable->numUsedFile += 1;
									return fd;
								}
							}
						}
					}
					
				}
				else if(strcmp(cursor->name, "") == 0) {
					strcpy(cursor->name, file_arr[idx - 1]);
					cursor->inodeNum = free_inode;
					PutDirEntry(sub_block, i % NUM_OF_DIRENT_PER_BLK, cursor);

					GetInode(free_inode, pInode);
					pInode->size = 0;
					pInode->type = FILE_TYPE_FILE;
					PutInode(free_inode, pInode);

					SetInodeBytemap(free_inode);

					DevReadBlock(0, buf);
					fileSysInfo = (FileSysInfo*)buf;
					fileSysInfo->numAllocInodes += 1;
					DevWriteBlock(0, buf);
					for(int i = 0; i < DESC_ENTRY_NUM; i++) {
                        if(pFileDescTable->pEntry[i].bUsed == 0) {
                            pFileDescTable->pEntry[i].bUsed = 1;
                            fd = i;
							file->inodeNum = free_inode;
							file->fileOffset = 0;
							file->bUsed = 1;
							for(int j = 0; j < MAX_FILE_NUM; j++) {
								if(pFileTable->pFile[j].bUsed == 0) {
									pFileTable->pFile[j] = *file;
									pFileTable->pFile[j].bUsed = 1;
									pFileDescTable->pEntry[i].fileTableIndex = j;
									pFileTable->numUsedFile += 1;
									pFileDescTable->numUsedDescEntry += 1;
									return fd; 
								}
							}

                        }
                    }					
				}
			}
		}
	}
}

int WriteFile(int fileDesc, char* pBuffer, int length)
{
	char* buf = (char*)malloc(BLOCK_SIZE);
	FileSysInfo* fileSysInfo = (FileSysInfo*)malloc(sizeof(FileSysInfo));
	int block_num = GetFreeBlockNum();
	int file_index = pFileDescTable->pEntry[fileDesc].fileTableIndex;

	int indirect_block;
	int indirect_cursor;
	int found_block;
	int found_cursor;
	File file = pFileTable->pFile[file_index];
	Inode* pInode = (Inode*)malloc(sizeof(Inode));
	GetInode(file.inodeNum, pInode);

	for(int i = 0; i < 4; i++) {
		if(pInode->dirBlockPtr[i] == 0) {
			pInode->dirBlockPtr[i] = block_num;
			SetBlockBytemap(block_num);
			pInode->allocBlocks += 1;
			PutInode(file.inodeNum, pInode);

			DevReadBlock(0, buf);
			fileSysInfo = (FileSysInfo*)buf;
			fileSysInfo->numAllocBlocks += 1;
			fileSysInfo->numFreeBlocks -= 1;
			DevWriteBlock(0, buf);

			strcpy(buf, pBuffer);
			DevWriteBlock(block_num, buf);
			file.fileOffset += length;
			return 0;
		}
	}
	
	if(pInode->indirectBlockPtr == 0) {
		pInode->indirectBlockPtr = block_num;
		memset(buf, 0, BLOCK_SIZE);
		DevWriteBlock(block_num, buf);
		SetBlockBytemap(block_num);
		PutInode(file.inodeNum, pInode);

		block_num = GetFreeBlockNum();
		PutIndirectBlockEntry(pInode->indirectBlockPtr, 0, block_num);
		pInode->allocBlocks += 1;
		PutInode(file.inodeNum, pInode);
		SetBlockBytemap(block_num);
        found_block = GetIndirectBlockEntry(pInode->indirectBlockPtr, 0);

		strcpy(buf, pBuffer);
		DevWriteBlock(found_block, buf);
		file.fileOffset += length;

		DevReadBlock(0, buf);
		fileSysInfo = (FileSysInfo*)buf;
		fileSysInfo->numAllocBlocks += 1;
		fileSysInfo->numFreeBlocks -= 1;
		DevWriteBlock(0, buf);
		return 0;
	}

	else {
		int idx;
		for(int i = 0; i < BLOCK_SIZE / sizeof(int); i++) {
			int num = GetIndirectBlockEntry(pInode->indirectBlockPtr, i);
			if(num == 0) {
				idx = i;
				break;
			}
		}
		block_num = GetFreeBlockNum();
		memset(buf, 0, BLOCK_SIZE);
		DevWriteBlock(block_num, buf);
		SetBlockBytemap(block_num);

		PutIndirectBlockEntry(pInode->indirectBlockPtr, idx, block_num);
		strcpy(buf, pBuffer);
		DevWriteBlock(block_num, buf);
		file.fileOffset += length;
		pInode->allocBlocks += 1;
		PutInode(file.inodeNum, pInode);

		DevReadBlock(0, buf);
		fileSysInfo = (FileSysInfo*)buf;
		fileSysInfo->numAllocBlocks += 1;
		fileSysInfo->numFreeBlocks -= 1;
		DevWriteBlock(0, buf);
		return 0;
	}
	return -1;
}


int ReadFile(int fileDesc, char* pBuffer, int length)
{
	File file;
	Inode* pInode = (Inode*)malloc(sizeof(Inode));
	char* buf = (char*)malloc(BLOCK_SIZE);

	int file_table_index = pFileDescTable->pEntry[fileDesc].fileTableIndex;
	file = pFileTable->pFile[file_table_index];
	int block = length / BLOCK_SIZE;
	int data = 0;
	int i = 0;
	GetInode(file.inodeNum, pInode);
	if(block < 4) {
		DevReadBlock(pInode->dirBlockPtr[block], buf);
		strcpy(pBuffer, buf);
		while(pBuffer[i] != 0) {
			data += 1;
			i += 1;
		}
		return data;
	}

	else {
		int indir_block = block - 4;
		int indir = pInode->indirectBlockPtr;
		i = 0;
		GetIndirectBlockEntry(pInode->indirectBlockPtr, indir_block);
		DevReadBlock(indir_block, buf);
		strcpy(pBuffer, buf);
		while(pBuffer[i] != 0) {
			data += 1;
			i += 1;
		}
		return data;
	}
}

int CloseFile(int fileDesc)
{
	File* file = malloc(sizeof(File));
	int file_table_index = pFileDescTable->pEntry[fileDesc].fileTableIndex;
	pFileTable->pFile[file_table_index].bUsed = 0;
	pFileTable->numUsedFile -= 1;
	pFileTable->pFile[file_table_index] = *file;
	free(file);
	pFileDescTable->pEntry[fileDesc].bUsed = 0;
	pFileDescTable->pEntry[fileDesc].fileTableIndex = 0;
	pFileDescTable->numUsedDescEntry -= 1;	
	return 0;	
}

int RemoveFile(char* name)
{

}


int MakeDirectory(char* name)
{
	int block_num = GetFreeBlockNum();
	int free_inode = GetFreeInodeNum();

	FileSysInfo* fileSysInfo = (FileSysInfo*)malloc(sizeof(FileSysInfo));
	int sub_block;
	char path_name[MAX_NAME_LEN];
	strcpy(path_name, name);

	// (2) - 1
	Inode* pInode = (Inode *)malloc(sizeof(Inode));
	GetInode(0, pInode);
	Inode* parent = (Inode*)malloc(sizeof(Inode));

	// (2) - 2
	char* buf = (char*)malloc(BLOCK_SIZE);
	DirEntry* cursor = (DirEntry*)malloc(sizeof(DirEntry));

	char* path_arr[MAX_NAME_LEN];
	int idx = 0;
	int i = 0;
	char* tmp = strtok(path_name, "/");

	while(tmp != NULL) {
		*(path_arr + idx) = tmp;
		idx++;
		tmp = strtok(NULL, "/");
	}

	int	path_block = find_path(i, idx, path_arr, pInode, buf);
	if(path_block == -1) {
		return -1;
	}

	GetDirEntry(path_block, 0, cursor);
	int parent_inode = cursor->inodeNum;
	GetInode(parent_inode, parent);
	for(int i = 0; i < NUM_OF_DIRENT_PER_BLK; i++) {
		if(GetDirEntry(path_block, i, cursor) == 1) {
			if(strcmp(cursor->name, path_arr[idx - 1]) == 0) {
				return -1;
			}
			else if(i < 8 && strcmp(cursor->name, "") == 0) {
				strcpy(cursor->name, path_arr[idx - 1]);
				cursor->inodeNum = free_inode;
				PutDirEntry(path_block, i, cursor);
				GetDirEntry(block_num, 0, cursor);
				strcpy(cursor->name, ".");
				cursor->inodeNum = free_inode;
				PutDirEntry(block_num, 0, cursor);
				
				GetDirEntry(block_num, 1, cursor);
				strcpy(cursor->name, "..");
				cursor->inodeNum = parent_inode;
				PutDirEntry(block_num, 1, cursor);

				GetInode(free_inode, pInode);
				pInode->dirBlockPtr[0] = block_num;
				pInode->allocBlocks = 1;
				pInode->size = 512;
				pInode->type = FILE_TYPE_DIR;
				PutInode(free_inode, pInode);
				
				SetBlockBytemap(block_num);
				SetInodeBytemap(free_inode);

				DevReadBlock(0, buf);
				fileSysInfo = (FileSysInfo*)buf;
				fileSysInfo->numAllocBlocks += 1;
				fileSysInfo->numFreeBlocks -= 1;
				fileSysInfo->numAllocInodes += 1;
				DevWriteBlock(0, buf);

				return 0;
			}
		}
	}
	for(int i = 8; i < NUM_OF_DIRENT_PER_BLK * NUM_OF_DIRECT_BLOCK_PTR; i++) {
		if(parent->dirBlockPtr[i / NUM_OF_DIRENT_PER_BLK] == 0) {
			sub_block = GetFreeBlockNum();
			parent->dirBlockPtr[i / NUM_OF_DIRENT_PER_BLK] = sub_block;
			parent->allocBlocks += 1;
			PutInode(parent_inode, parent);
			SetBlockBytemap(sub_block);

			DevReadBlock(0, buf);
			fileSysInfo = (FileSysInfo*)buf;
			fileSysInfo->numAllocBlocks += 1;
			fileSysInfo->numFreeBlocks -= 1;
			DevWriteBlock(0, buf);
		}
		if(GetDirEntry(parent->dirBlockPtr[i / NUM_OF_DIRENT_PER_BLK], i % NUM_OF_DIRENT_PER_BLK, cursor) == 1) {
			if(strcmp(cursor->name, path_arr[idx - 1]) == 0) {
				return -1;
			}
			else if(strcmp(cursor->name, "") == 0) {
				block_num = GetFreeBlockNum();
				strcpy(cursor->name, path_arr[idx - 1]);
				cursor->inodeNum = free_inode;
				PutDirEntry(sub_block, i % NUM_OF_DIRENT_PER_BLK, cursor);

				GetDirEntry(block_num, 0, cursor);
				strcpy(cursor->name, ".");
				cursor->inodeNum = free_inode;
				PutDirEntry(block_num, 0, cursor);

				GetDirEntry(block_num, 1, cursor);
				strcpy(cursor->name, "..");
				cursor->inodeNum = parent_inode;
				PutDirEntry(block_num, 1, cursor);

				GetInode(free_inode, pInode);
				pInode->dirBlockPtr[0] = block_num;
				pInode->allocBlocks = 1;
				pInode->size = 512;
				pInode->type = FILE_TYPE_DIR;
				PutInode(free_inode, pInode);

				SetBlockBytemap(block_num);
				SetInodeBytemap(free_inode);

				DevReadBlock(0, buf);
				fileSysInfo = (FileSysInfo*)buf;
				fileSysInfo->numAllocBlocks += 1;
				fileSysInfo->numFreeBlocks -= 1;
				fileSysInfo->numAllocInodes += 1;
				DevWriteBlock(0, buf);
				return 0;
			}
		}		
	}

	// indirect Block
	GetDirEntry(path_block, 0, cursor);
	parent_inode = cursor->inodeNum;
	GetInode(parent_inode, parent);
	char* indirect = (char*)malloc(BLOCK_SIZE);
	int indirect_block;
	int found;
	if(parent->indirectBlockPtr == 0) {
		sub_block = GetFreeBlockNum();
		parent->indirectBlockPtr = sub_block;
		memset(indirect, 0, BLOCK_SIZE);
		DevWriteBlock(sub_block, indirect);
		PutInode(parent_inode, parent);
		SetBlockBytemap(sub_block);
	
		sub_block = GetFreeBlockNum();
		PutIndirectBlockEntry(parent->indirectBlockPtr, 0, sub_block);
		SetBlockBytemap(sub_block);

		indirect_block = GetIndirectBlockEntry(parent->indirectBlockPtr, 0);
		GetDirEntry(indirect_block, 0, cursor);
		strcpy(cursor->name, path_arr[idx - 1]);
		cursor->inodeNum = free_inode;
		PutDirEntry(indirect_block, 0, cursor);
		GetDirEntry(indirect_block, 0, cursor);

		block_num = GetFreeBlockNum();
		GetDirEntry(block_num, 0, cursor);
		strcpy(cursor->name, ".");
		cursor->inodeNum = free_inode;
		PutDirEntry(block_num, 0, cursor);

		GetDirEntry(block_num, 1, cursor);
		strcpy(cursor->name, "..");
		cursor->inodeNum = parent_inode;
		PutDirEntry(block_num, 1, cursor);
		
		GetInode(free_inode, pInode);
		pInode->dirBlockPtr[0] = block_num;
		pInode->size = 512;
		pInode->type = FILE_TYPE_DIR;
		pInode->allocBlocks = 1;
		PutInode(free_inode, pInode);
		
		parent->allocBlocks += 1;
		PutInode(parent_inode, parent);
		DevReadBlock(0, buf);
		fileSysInfo = (FileSysInfo*)buf;
		fileSysInfo->numAllocBlocks += 2;
		fileSysInfo->numFreeBlocks -= 2;
		fileSysInfo->numAllocInodes += 1;
		DevWriteBlock(0, buf);

		SetBlockBytemap(block_num);
		SetInodeBytemap(free_inode);
		int num = GetIndirectBlockEntry(parent->indirectBlockPtr, 0);
		return 0;
	}

	else {
		for(int i = 0; i < BLOCK_SIZE / sizeof(int); i++) {
			indirect_block = GetIndirectBlockEntry(parent->indirectBlockPtr, i);
			if(indirect_block == 0) {
				sub_block = GetFreeBlockNum();
				PutIndirectBlockEntry(parent->indirectBlockPtr, i, sub_block);
				SetBlockBytemap(sub_block);
				indirect_block = GetIndirectBlockEntry(parent->indirectBlockPtr, i);
				parent->allocBlocks += 1;
				PutInode(parent_inode, parent);
				DevReadBlock(0, buf);
				fileSysInfo = (FileSysInfo*)buf;
				fileSysInfo->numAllocBlocks += 1;
				fileSysInfo->numFreeBlocks -= 1;
				DevWriteBlock(0, buf);
			}
			for(int j = 0; j < NUM_OF_DIRENT_PER_BLK; j++) {
				GetDirEntry(indirect_block, j, cursor);
				if(strcmp(cursor->name, "") == 0) {
					found = 1;
					strcpy(cursor->name, path_arr[idx - 1]);
					cursor->inodeNum = free_inode;
					PutDirEntry(indirect_block, j, cursor);
					
					block_num = GetFreeBlockNum();	
					GetDirEntry(block_num, 0, cursor);
					strcpy(cursor->name, ".");
					cursor->inodeNum = free_inode;
					PutDirEntry(block_num, 0, cursor);

					GetDirEntry(block_num, 1, cursor);
					strcpy(cursor->name, "..");
					cursor->inodeNum = parent_inode;
					PutDirEntry(block_num, 1, cursor);
						
					GetInode(free_inode, pInode);
					pInode->dirBlockPtr[0] = block_num;
					pInode->size = 512;
					pInode->type = FILE_TYPE_DIR;
					pInode->allocBlocks = 1;
					PutInode(free_inode, pInode);

					DevReadBlock(0, buf);
					fileSysInfo = (FileSysInfo*)buf;
					fileSysInfo->numAllocBlocks += 1;
					fileSysInfo->numFreeBlocks -= 1;
					fileSysInfo->numAllocInodes += 1;
					DevWriteBlock(0, buf);

					SetBlockBytemap(block_num);
					SetInodeBytemap(free_inode);
					return 1;
				}
			}
		}
	}
	return -1;
}


int RemoveDirectory(char* name)
{
    Inode* pInode = (Inode*)malloc(sizeof(Inode));
	Inode* tmp_node = (Inode*)malloc(sizeof(Inode));
	memset(tmp_node, 0, sizeof(Inode));

    GetInode(0, pInode);
    FileSysInfo* fileSysInfo = (FileSysInfo*)malloc(sizeof(FileSysInfo));

    char* buf = (char*)malloc(BLOCK_SIZE);
    DevReadBlock(pInode->dirBlockPtr[0], buf);
	char* tmp_buf = (char*)malloc(BLOCK_SIZE);

    DirEntry* cursor = (DirEntry*)malloc(sizeof(DirEntry));
    char dir_name[MAX_NAME_LEN];
    strcpy(dir_name, name);
    
    char*tmp = strtok(dir_name, "/");
    int idx = 0;
    char* dir_arr[MAX_NAME_LEN];
    int found = 0;
	int i = 0;
	int parent_block;
	int parent_index;
	
	block_index = 0;
	idx = 0;
	idx2 = 0;

    while(tmp != NULL) {
        *(dir_arr + idx) = tmp;
        idx++;
        tmp = strtok(NULL, "/");
    } 
  
    int block = find_path(i, idx, dir_arr, pInode, buf);
	GetDirEntry(block, 0, cursor);
	GetInode(cursor->inodeNum, pInode);
	int parent_inode = cursor->inodeNum;

	// find entry
	for(int i = 0; i < NUM_OF_DIRENT_PER_BLK * NUM_OF_DIRECT_BLOCK_PTR; i++) {
		GetDirEntry(pInode->dirBlockPtr[i / NUM_OF_DIRENT_PER_BLK], i % NUM_OF_DIRENT_PER_BLK, cursor);
		if(strcmp(cursor->name, dir_arr[idx - 1]) == 0) {
			GetInode(cursor->inodeNum, tmp_node);
			found = 1;
			parent_block = pInode->dirBlockPtr[i / NUM_OF_DIRENT_PER_BLK];
			parent_index = i % NUM_OF_DIRENT_PER_BLK;
			break;
		}
	}
	if(found == 0 && pInode->indirectBlockPtr == 0) {
		return -1;
	}
	else if(found == 1) {
		int current_inode = cursor->inodeNum;
		for(int i = 0; i < NUM_OF_DIRENT_PER_BLK * NUM_OF_DIRECT_BLOCK_PTR; i++) {
			GetDirEntry(tmp_node->dirBlockPtr[i / NUM_OF_DIRENT_PER_BLK], i % NUM_OF_DIRENT_PER_BLK, cursor);
			if(strcmp(cursor->name, ".") == 0 || strcmp(cursor->name, "..") == 0) {
				continue;
			}
			else if(strcmp(cursor->name, "") != 0) {
				return -1;
			}
		}	
		ResetBlockBytemap(tmp_node->dirBlockPtr[0]);
		memset(buf, 0, BLOCK_SIZE);
		DevWriteBlock(tmp_node->dirBlockPtr[0], buf);

		memset(tmp_node, 0, sizeof(Inode));
		PutInode(current_inode, tmp_node);

		GetDirEntry(parent_block, parent_index, cursor);

		if(parent_index == 0) {
			pInode->dirBlockPtr[parent_block] = 0;
			pInode->allocBlocks -= 1;
			PutInode(parent_inode, pInode);

			memset(buf, 0, BLOCK_SIZE);
			DevWriteBlock(parent_block, buf);

			DevReadBlock(0, tmp_buf);
			fileSysInfo = (FileSysInfo*)tmp_buf;
			fileSysInfo->numAllocBlocks -= 2;
			fileSysInfo->numAllocInodes -= 1;
			fileSysInfo->numFreeBlocks += 2;
			DevWriteBlock(0, tmp_buf);

			ResetBlockBytemap(parent_block);
			ResetInodeBytemap(current_inode);
			return 0;
		}		
		strcpy(cursor->name, "");
		cursor->inodeNum = 0;
		PutDirEntry(parent_block, parent_index, cursor);

		DevReadBlock(0, tmp_buf);
		fileSysInfo = (FileSysInfo*)tmp_buf;
		fileSysInfo->numAllocBlocks -= 1;
		fileSysInfo->numAllocInodes -= 1;
		fileSysInfo->numFreeBlocks += 1;
		DevWriteBlock(0, tmp_buf);
		ResetInodeBytemap(current_inode);
		return 0;
	}

	GetInode(parent_inode, pInode);
	if(pInode->indirectBlockPtr != 0) {
		int indirect_block = pInode->indirectBlockPtr;
		int indirect_cursor = 0;
		int found_block = 0;
		int block_cursor = 0;
		int result_block = 0;
		int result_cursor = 0;
		int get = 0;
		int indirect_block_num;

		for(int i = 0; i < BLOCK_SIZE / sizeof(int); i++) {
			found_block = GetIndirectBlockEntry(indirect_block, i);
			block_cursor = i;
			if(found_block == 0) {
				return -1;
			}
			else {
				indirect_block_num += 1;
			}
			for(int j = 0; j < NUM_OF_DIRENT_PER_BLK; j++) {
				GetDirEntry(found_block, j, cursor);
				if(strcmp(cursor->name, dir_arr[idx - 1]) == 0) {
					get = 1;
					result_block = found_block;
					result_cursor = j;
					break;
				}
			}	
			if(get == 1) {
				break;
			}
		}

		if(get == 1) {
			DevReadBlock(0, buf);
			fileSysInfo = (FileSysInfo*)buf;
			GetDirEntry(result_block, result_cursor, cursor);
			GetInode(cursor->inodeNum, tmp_node);
			GetInode(cursor->inodeNum, pInode);
			int cur_inode = cursor->inodeNum;
			
			for(int i = 0; i < NUM_OF_DIRENT_PER_BLK; i++) {
				GetDirEntry(tmp_node->dirBlockPtr[0], i, cursor);
				if(strcmp(cursor->name, ".") == 0 || strcmp(cursor->name, "..") == 0) {
					continue;
				}
				else if(strcmp(cursor->name, "") != 0) {
					return -1;
				}
			}
			
			ResetBlockBytemap(tmp_node->dirBlockPtr[0]);
			memset(buf, 0, BLOCK_SIZE);
			DevWriteBlock(tmp_node->dirBlockPtr[0], buf);
			memset(tmp_node, 0, sizeof(Inode));
			PutInode(cur_inode, tmp_node);			
			ResetInodeBytemap(cur_inode);

			if(result_cursor == 0) {
				DevReadBlock(result_block, buf);
				RemoveIndirectBlockEntry(indirect_block, block_cursor);
				memset(buf, 0, BLOCK_SIZE);
				DevWriteBlock(result_block, buf);
				ResetBlockBytemap(result_block);
				indirect_block_num -= 1;
				if(indirect_block_num == 0) {
					GetInode(parent_inode, tmp_node);
					ResetBlockBytemap(tmp_node->indirectBlockPtr);
					tmp_node->indirectBlockPtr = 0;
					PutInode(parent_inode, tmp_node);
				}
				GetInode(parent_inode, tmp_node);
				tmp_node->allocBlocks -= 1;
				PutInode(parent_inode, tmp_node);
				DevReadBlock(0, tmp_buf);
				fileSysInfo = (FileSysInfo*)tmp_buf;
				fileSysInfo->numAllocBlocks -= 2;
				fileSysInfo->numFreeBlocks += 2;
				fileSysInfo->numAllocInodes -= 1;
				DevWriteBlock(0, tmp_buf);
				return 0;
			}
			else {
				GetDirEntry(result_block, result_cursor, cursor);
				strcpy(cursor->name, "");
				cursor->inodeNum = 0;
				PutDirEntry(result_block, result_cursor, cursor);

				DevReadBlock(0, tmp_buf);
				fileSysInfo = (FileSysInfo*)tmp_buf;
				fileSysInfo->numAllocBlocks -= 1;
				fileSysInfo->numFreeBlocks += 1;
				fileSysInfo->numAllocInodes -= 1;
				DevWriteBlock(0, tmp_buf);
				return 0;
			}
		}
		else {
			return -1;
		}	
	}
	return -1;
}


void CreateFileSystem(void)
{
	FileSysInit();
	
	int block_num = GetFreeBlockNum();
	int free_inode = GetFreeInodeNum();
	FileSysInfo* fileSysInfo = (FileSysInfo*)malloc(sizeof(FileSysInfo));

	char* buf = (char*)malloc(BLOCK_SIZE);
	DevReadBlock(0, buf);

	DirEntry* cursor = (DirEntry*)malloc(sizeof(DirEntry));

	pFileDescTable = (FileDescTable*)malloc(sizeof(FileDescTable));
	memset(pFileDescTable, 0, sizeof(FileDescTable));	
	pFileTable = (FileTable*)malloc(sizeof(FileTable));
	memset(pFileTable, 0, sizeof(FileTable));

	GetDirEntry(block_num, 0, cursor);
	strcpy(cursor->name, ".");
	cursor->inodeNum = free_inode;
	PutDirEntry(block_num, 0, cursor);

	fileSysInfo = (FileSysInfo*)buf;
	fileSysInfo->blocks = BLOCK_SIZE;
	fileSysInfo->rootInodeNum = free_inode;
	fileSysInfo->diskCapacity = FS_DISK_CAPACITY;
	fileSysInfo->numAllocBlocks = 0;
	fileSysInfo->numFreeBlocks = 505;
	fileSysInfo->numAllocInodes = 0;
	fileSysInfo->blockBytemapBlock = 2;
	fileSysInfo->inodeBytemapBlock = 1;
	fileSysInfo->inodeListBlock = 3;
	fileSysInfo->dataRegionBlock = 7;

	fileSysInfo->numAllocBlocks += 1;
	fileSysInfo->numFreeBlocks -= 1;
	fileSysInfo->numAllocInodes += 1;

	DevWriteBlock(0, buf);

	SetBlockBytemap(block_num);
	SetInodeBytemap(free_inode);
	
	Inode* pInode = (Inode*)malloc(sizeof(Inode));
	GetInode(free_inode, pInode);

	pInode->dirBlockPtr[0] = block_num;
	pInode->size = 512;
	pInode->type = FILE_TYPE_DIR;
	pInode->allocBlocks = 1;
	PutInode(0, pInode);

}

void OpenFileSystem(void)
{
	DevOpenDisk();
	pFileDescTable = (FileDescTable*)malloc(sizeof(FileDescTable));
	memset(pFileDescTable, 0, sizeof(FileDescTable));
	pFileTable = (FileTable*)malloc(sizeof(FileTable));
	memset(pFileTable, 0, sizeof(FileTable));
}

void CloseFileSystem(void)
{
	DevCloseDisk();
}

Directory* OpenDirectory(char* name)
{
	Directory* dir = (Directory*)malloc(sizeof(Directory));
	Inode* pInode = (Inode*)malloc(sizeof(Inode));
	GetInode(0, pInode);
	
	char* buf = (char*)malloc(BLOCK_SIZE);
	DevReadBlock(pInode->dirBlockPtr[0], buf);

	DirEntry* cursor = (DirEntry*)malloc(sizeof(DirEntry));
	char dir_name[MAX_NAME_LEN];
	strcpy(dir_name, name);
	
	char*tmp = strtok(dir_name, "/");
	int idx = 0;
	char* dir_arr[MAX_NAME_LEN];
	int i = 0;

	while(tmp != NULL) {
		*(dir_arr + idx) = tmp;
		idx++;
		tmp = strtok(NULL, "/");
	}
	int block = find_path(i, idx + 1, dir_arr, pInode, buf);
	// block = 0 : file
	if(block == -1 || block == 0) {
		free(buf);
		free(dir);
		free(pInode);
		free(cursor);
		return NULL;
	}
	
	GetDirEntry(block, 0, cursor);
	GetInode(cursor->inodeNum, pInode);

	if(pInode->type == FILE_TYPE_DIR) {
		dir->inodeNum = cursor->inodeNum;
		free(buf);
		free(pInode);
		free(cursor);
		return dir;
	}
	free(buf);
	free(pInode);
	free(cursor);
	return NULL;
}


FileInfo* ReadDirectory(Directory* pDir)
{
	FileInfo* info = (FileInfo*)malloc(sizeof(FileInfo));
	Inode* pInode = (Inode*)malloc(sizeof(Inode));
	pCursor = (DirEntry*)malloc(sizeof(DirEntry));
	Inode* tmp_node = (Inode*)malloc(sizeof(Inode));
	DirEntry* tmp_cur = (DirEntry*)malloc(sizeof(DirEntry));

	GetInode(pDir->inodeNum, pInode);
	int block1 = pInode->dirBlockPtr[0];
	int block2 = pInode->dirBlockPtr[1];
	int block3 = pInode->dirBlockPtr[2];
	int block4 = pInode->dirBlockPtr[3];
	int indirect_block = pInode->indirectBlockPtr;
	int block_arr[5] = {block1, block2, block3, block4, indirect_block};
	GetDirEntry(block_arr[0], idx, pCursor);
	while(idx <= 8) {
		if(idx == 8) {
			idx = 0;
			block_index += 1;
			if(block_index >= 4) {
				break;
			}
			if(block_arr[block_index] == 0) {
				block_index = 0;
				return NULL;
			}
		}
		else if(block_index >= 4) {
			break;
		}
		GetDirEntry(block_arr[block_index], idx, pCursor);
		if(strcmp(pCursor->name, "") == 0) {
			idx = 0;
			block_index = 0;
			return NULL;
		}
		GetInode(pCursor->inodeNum, tmp_node);
		strcpy(info->name, pCursor->name);
        info->filetype = tmp_node->type;
        info->inodeNum = pCursor->inodeNum;
        info->numBlocks = tmp_node->allocBlocks;
        info->size = tmp_node->size;
		idx += 1;
        return info;
	}
	
	if(block_arr[block_index] == 0) {
		return NULL;
	}

	else {
		indirBlock_index = pInode->indirectBlockPtr;
		int num = GetIndirectBlockEntry(indirBlock_index, idx2);
		while(GetIndirectBlockEntry(indirBlock_index, idx2) != 0) {
			GetDirEntry(num, cursor_index, tmp_cur);
			num = GetIndirectBlockEntry(indirBlock_index, idx2);
			while(cursor_index <= 8) {
				if(cursor_index == 8) {
					cursor_index = 0;
					idx2 += 1;
					break;
				}
				GetDirEntry(num, cursor_index, pCursor);
				if(strcmp(pCursor->name, "") == 0) {
					idx2 = 0;
					cursor_index = 0;
					return NULL;
				}
				GetInode(pCursor->inodeNum, tmp_node);
				strcpy(info->name, pCursor->name);
				info->filetype = tmp_node->type;
				info->inodeNum = pCursor->inodeNum;
				info->numBlocks = tmp_node->allocBlocks;
				info->size = tmp_node->size;
				cursor_index += 1;
				return info;
			}	
		}
	}
	block_index = 0;
	cursor_index = 0;
	idx = 0;
	idx2 = 0;
	return NULL;
}

int CloseDirectory(Directory* pDir)
{
	free(pDir);
	return 0;
}
