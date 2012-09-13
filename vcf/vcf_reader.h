#ifndef VCF_READER_H
#define VCF_READER_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <zlib.h>

#include <commons/file_utils.h>
#include <commons/log.h>
#include <containers/list.h>

#include "vcf_util.h"
#include "vcf_file_structure.h"
#include "vcf_batch.h"

#define CHUNK 0x80000

extern int mmap_vcf;


typedef struct {
    vcf_record_t *current_record;
    vcf_header_entry_t *current_header_entry;
    vcf_batch_t *current_batch;
    
    size_t num_samples;
    size_t num_records;
    
    int store_samples;
    int self_contained; // TODO this could not be neccessary, need to check
} vcf_reader_status;

/**
 * 
 * @param p Pointer to the beginning of the input buffer
 * @param pe Pointer to the end of the input buffer
 * @param batches_list List where the read batches will be appended
 * @param batch_size The number of lines of a batch, or zero when its size is specified in bytes
 * @param file VCF file whose contents will be read
 * @param status Structure that stores the current status of the parser
 */
int execute_vcf_ragel_machine(char *p, char *pe, list_t *batches_list, size_t batch_size, vcf_file_t *file, vcf_reader_status *status);

vcf_reader_status *vcf_reader_status_new(size_t batch_size, int store_samples, int self_contained);

void vcf_reader_status_free(vcf_reader_status *status);


int vcf_read_and_parse(list_t *batches_list, size_t batch_size, vcf_file_t *file, int read_samples);

int vcf_read_and_parse_bytes(list_t *batches_list, size_t batch_size, vcf_file_t *file, int read_samples);

int vcf_gzip_read_and_parse(list_t *batches_list, size_t batch_size, vcf_file_t *file, int read_samples);

int vcf_gzip_read_and_parse_bytes(list_t *batches_list, size_t batch_size, vcf_file_t *file, int read_samples);


int vcf_light_read(list_t *batches_list, size_t batch_size, vcf_file_t *file);

int vcf_light_read_bytes(list_t *batches_list, size_t batch_size, vcf_file_t *file);

int vcf_gzip_light_read(list_t *batches_list, size_t batch_size, vcf_file_t *file);

int vcf_gzip_light_read_bytes(list_t *batches_list, size_t batch_size, vcf_file_t *file);


int vcf_light_multiread(list_t **batches_list, size_t batch_size, vcf_file_t **files, size_t num_files);


size_t consume_input(int c, char **data, size_t max_len, int position_in_data);

#endif
