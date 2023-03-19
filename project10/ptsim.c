#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MEM_SIZE 16384  // MUST equal PAGE_SIZE * PAGE_COUNT
#define PAGE_SIZE 256  // MUST equal 2^PAGE_SHIFT
#define PAGE_COUNT 64
#define PAGE_SHIFT 8  // Shift page number this much

#define PTP_OFFSET 64 // How far offset in page 0 is the page table pointer table

// Simulated RAM
unsigned char mem[MEM_SIZE];

//
// Convert a page,offset into an address
//
int get_address(int page, int offset)
{
    return (page << PAGE_SHIFT) | offset;           // VPN BITS + OFFSET BITS
}

//
// Initialize RAM
//
void initialize_mem(void)
{
    memset(mem, 0, MEM_SIZE);

    int zpfree_addr = get_address(0, 0);
    mem[zpfree_addr] = 1;  // Mark zero page as allocated
}

//
// Get the page table page for a given process
//
unsigned char get_page_table(int proc_num)
{
    int ptp_addr = get_address(0, PTP_OFFSET + proc_num);
    return mem[ptp_addr];
}

//
// Get physical page for associated virtual page
//
int get_physical_addr(int proc_num, int virtual_addr){
    int virtual_page = virtual_addr >> 8;
    int offset = virtual_addr & 255;
    int page_table = get_page_table(proc_num);
    int phys_page = mem[get_address(page_table, virtual_page)];
    int phys_addr = (phys_page << 8) | offset; 

    return phys_addr;
}

void store_value(int proc_num, int virt_addr, int value){
    int phys_addr = get_physical_addr(proc_num, virt_addr);
    mem[phys_addr] = value;
    printf("Store proc %d: %d => %d, value=%d\n", proc_num, virt_addr, phys_addr, value);
}

void load_value(int proc_num, int virt_addr){
    int phys_addr = get_physical_addr(proc_num, virt_addr);
    int value = mem[phys_addr];
    printf("Load proc %d: %d => %d, value=%d\n", proc_num, virt_addr, phys_addr, value);
}


int allocate_page(){
    for(int page_num = 0; page_num< PAGE_COUNT; page_num++)
        if(mem[page_num] == 0){
            mem[page_num] = 1;
            return page_num;
        }
     return 0xff;    
}

//
// Deallocates pages setting value to 0
//

void deallocate_page(int page_num){
        mem[page_num]=0;
}

//
// Deallocates procedure pages and its associated page_table
//

void kill_process(int proc_num){
    int page_table = get_page_table(proc_num);

    for(int i=0; i < PAGE_COUNT; ++i){
        int ptp_addr = get_address(page_table, i);
        if(mem[ptp_addr] != 0){
            deallocate_page(mem[ptp_addr]);
        }
    }
    deallocate_page(page_table);
}


//
// Allocate pages for a new process
//
// This includes the new process page table and page_count data pages.
//
void new_process(int proc_num, int page_count)
{
    int page_table = allocate_page();

    if(page_table == 0xff){
            printf("OOM: proc %d: page table\n", proc_num);
            return;
    }

    mem[64 + proc_num] = page_table;

    // Set the page table to map virt -> phys // Virtual page number is i // Physical page number is new_page
    for(int i = 0; i < page_count; i++){
        int new_page = allocate_page();

        if(new_page == 0xff){
            printf("OOM: proc %d: data page\n", proc_num);
            return;
        }

        int pt_addr = get_address(page_table, i);
        mem[pt_addr] = new_page;
    }

}

//
// Print the free page map
//
// Don't modify this
//
void print_page_free_map(void)
{
    printf("--- PAGE FREE MAP ---\n");

    for (int i = 0; i < 64; i++) {
        int addr = get_address(0, i);

        printf("%c", mem[addr] == 0? '.': '#');

        if ((i + 1) % 16 == 0)
            putchar('\n');
    }
}

//
// Print the address map from virtual pages to physical
//
// Don't modify this
//
void print_page_table(int proc_num)
{
    printf("\n--- PROCESS %d PAGE TABLE ---\n", proc_num);

    // Get the page table for this process
    int page_table = get_page_table(proc_num);

    // Loop through, printing out used pointers
    for (int i = 0; i < PAGE_COUNT; i++) {
        int addr = get_address(page_table, i);

        int page = mem[addr];

        if (page != 0) {
            printf("%02x -> %02x\n", i, page);
        }
    }
}

//
// Main -- process command line
//
int main(int argc, char *argv[])
{
    assert(PAGE_COUNT * PAGE_SIZE == MEM_SIZE);

    if (argc == 1) {
        fprintf(stderr, "usage: ptsim commands\n");
        return 1;
    }
    
    initialize_mem();

    for (int i = 1; i < argc; i++) {                        

        if (strcmp(argv[i], "np") == 0) {             
            int proc_num = atoi(argv[++i]);
            int page_count = atoi(argv[++i]);
            new_process(proc_num, page_count);
        }
        else if (strcmp(argv[i], "pfm") == 0) {             // Check for print free map
            print_page_free_map();
        }
        else if (strcmp(argv[i], "ppt") == 0) {             // Check for print page table
            int proc_num = atoi(argv[++i]);
            print_page_table(proc_num);
        }
        else if (strcmp(argv[i], "kp") == 0) {             // Check for print page table
            int proc_num = atoi(argv[++i]);
            kill_process(proc_num);
        }
        else if (strcmp(argv[i], "sb") == 0) {             // Check for print page table
            int proc_num = atoi(argv[++i]);
            int virt_addr = atoi(argv[++i]);
            int value = atoi(argv[++i]);
            store_value(proc_num, virt_addr, value);
        }
        else if (strcmp(argv[i], "lb") == 0) {             // Check for print page table
            int proc_num = atoi(argv[++i]);
            int virt_addr = atoi(argv[++i]);
            load_value(proc_num, virt_addr);
        }

    }

    return 0;
}
