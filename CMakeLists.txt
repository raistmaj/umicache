cmake_minimum_required (VERSION 3.1.0 FATAL_ERROR)
project (umicache)

add_executable(umicache 
				umicache.cpp
				umicache_exception.cpp
				umicache_cache.cpp
				umicache_command.cpp
				umicache_config.cpp
				redis/umicache_command_redis.cpp
				redis/umicache_config_redis.cpp
				redis/umicache_type_redis.cpp
				redis/commands/umicache_command_append.cpp
				redis/commands/umicache_command_auth.cpp
				redis/commands/umicache_command_bgrewriteaof.cpp
				redis/commands/umicache_command_bgsave.cpp
				redis/commands/umicache_command_bitcount.cpp
				redis/commands/umicache_command_bitop.cpp
				redis/commands/umicache_command_bitpos.cpp
				redis/commands/umicache_command_blpop.cpp
				redis/commands/umicache_command_brpop.cpp
				redis/commands/umicache_command_brpoplpush.cpp
				redis/commands/umicache_command_client_kill.cpp
				redis/commands/umicache_command_client_list.cpp
				redis/commands/umicache_command_client_getname.cpp
				redis/commands/umicache_command_client_pause.cpp
				redis/commands/umicache_command_client_setname.cpp
				redis/commands/umicache_command_cluster_addslots.cpp
				redis/commands/umicache_command_cluster_count_failure_reports.cpp
				redis/commands/umicache_command_cluster_countkeysinslot.cpp
				redis/commands/umicache_command_cluster_delslots.cpp
				redis/commands/umicache_command_cluster_failover.cpp
				redis/commands/umicache_command_cluster_forget.cpp
				redis/commands/umicache_command_cluster_getkeysinslot.cpp
				redis/commands/umicache_command_cluster_info.cpp
				redis/commands/umicache_command_cluster_keyslot.cpp
				redis/commands/umicache_command_cluster_meet.cpp
				redis/commands/umicache_command_cluster_nodes.cpp
				redis/commands/umicache_command_cluster_replicate.cpp
				redis/commands/umicache_command_cluster_reset.cpp
				redis/commands/umicache_command_cluster_saveconfig.cpp
				redis/commands/umicache_command_cluster_setconfigepoch.cpp
				redis/commands/umicache_command_cluster_setslot.cpp
				redis/commands/umicache_command_cluster_slaves.cpp
				redis/commands/umicache_command_cluster_slots.cpp
				redis/commands/umicache_command_command.cpp
				redis/commands/umicache_command_command_count.cpp
				redis/commands/umicache_command_command_getkeys.cpp
				redis/commands/umicache_command_command_info.cpp
				main.cpp)

set_property(TARGET umicache PROPERTY CXX_STANDARD 14)
set_property(TARGET umicache PROPERTY CXX_STANDARD_REQUIRED ON)
