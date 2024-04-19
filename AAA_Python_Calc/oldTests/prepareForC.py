large_number = 1424105634191099705056747106494719365430608463555621543718428964400580277438960802959063803080696423546229450006957874016169875701131043992787532735660816547338209360372278279261168144818108872211150169056502104585788788944312564735524179869266981542442774557560403514852962963366437859166841386057325

# Calculate how many 64-bit chunks are needed
num_bits = large_number.bit_length()
chunk_size_bits = 64
num_chunks = (num_bits + chunk_size_bits - 1) // chunk_size_bits  # Ceiling division

# Extract chunks of 64 bits
chunks = []
for i in range(num_chunks):
    # Shift right to get to the current chunk, and mask out all but the lowest 64 bits
    chunk = (large_number >> (i * chunk_size_bits)) & ((1 << chunk_size_bits) - 1)
    chunks.append(chunk)

# Since we generally list these in reverse order for little-endian representation:
chunks.reverse()

# Generate C code
c_code = "uint64_t m[{}] = {{".format(len(chunks)) + ", ".join(hex(chunk) for chunk in chunks) + "};"
print(c_code)