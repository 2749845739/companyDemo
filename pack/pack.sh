#!/bin/bash

cqtdp=`which cqtdeployer`
if [ ! $cqtdp ];then
	echo "Err: Please install cqtdeployer"
	exit 1
fi

qmake_bin=`which qmake`
if [ ! $qmake_bin ];then
	echo "Err: Please install qmake"
	exit 2
fi

if [ $# -ne 1 ];then
	echo "Usage: $0 <package version>"
	exit 3
fi

set -e

pack_src_dir=$(cd $(dirname $0);pwd)
repo_dir=$(cd $pack_src_dir/..;pwd)
repo_build_dir=$repo_dir/build
pack_dir=$repo_build_dir/$1
pack_p600_dir=$pack_dir/opt/P600

bin_dir=$pack_p600_dir/bin
lib_dir=$pack_p600_dir/lib

rm -rf $repo_build_dir
mkdir -p $pack_p600_dir

# 拷贝基础文件
cp -rf $pack_src_dir/DEBIAN $pack_dir
cp $pack_src_dir/start.sh $pack_src_dir/Ai-P600.desktop $pack_p600_dir


# 编译P600，并打包依赖库
cd $repo_build_dir;cmake ..;make -j3
ls $repo_build_dir/P600
cd $repo_build_dir;$cqtdp -bin $repo_build_dir/P600 -qmake $qmake_bin -qmlDir $repo_dir/UI -targetDir $pack_p600_dir

p600_bin=$bin_dir/P600
p600_deplist=$(ldd $p600_bin | awk  '{if (match($3,"/")){ printf("%s "),$3 } }')
cp $p600_deplist $lib_dir

# 打包配置文件项
cp -rf $pack_src_dir/database $pack_src_dir/flowmodel $pack_src_dir/config.ini $pack_src_dir/config.json $pack_src_dir/icon.png $bin_dir

# 编译插件，并打包依赖库
cd $repo_build_dir
camera_build_dir=$repo_build_dir/camera/build
camera_plugin_dir=$bin_dir/camera_plugin
camera_so=libdo3think_plugin.so
git clone -b develop git@192.168.1.101:gz-driver/camera.git
mkdir -p $camera_build_dir;cd $camera_build_dir;cmake ..;make -j
mkdir -p $camera_plugin_dir;cp -dp $camera_build_dir/do3think/${camera_so}* $camera_plugin_dir

camera_deplist=$(ldd $camera_plugin_dir/$camera_so | awk  '{if (match($3,"/")){ printf("%s "),$3 } }')
for dep_lib in $camera_deplist
do
	if [ "libdvp.so" = "$(basename $dep_lib)" ];then
		cp -rf $(dirname $dep_lib)/* $lib_dir
	else
		cp $dep_lib $lib_dir
	fi
done
# cp $camera_deplist $lib_dir

cd $repo_build_dir
board_build_dir=$repo_build_dir/board/build
board_plugin_dir=$bin_dir/board_plugin
board_so=libp600_plugin.so
git clone -b develop git@192.168.1.101:gz-driver/board.git
mkdir -p $board_build_dir;cd $board_build_dir;cmake ..;make -j
mkdir -p $board_plugin_dir;cp -dp $board_build_dir/p600/${board_so}* $board_plugin_dir

board_deplist=$(ldd $board_plugin_dir/$board_so | awk  '{if (match($3,"/")){ printf("%s "),$3 } }')
cp $board_deplist $lib_dir

cd $repo_build_dir
algorithm_build_dir=$repo_build_dir/p600algo/build
algorithm_plugin_dir=$bin_dir/graineval_plugin
algorithm_so=libalgorithm_p600.so
git clone -b dev git@192.168.1.101:product-repo/soft-dev/algorithm/p600algo.git
mkdir -p $algorithm_build_dir;cd $algorithm_build_dir;cmake ..;make -j
mkdir -p $algorithm_plugin_dir;cp -dp $algorithm_build_dir/src/${algorithm_so}* $algorithm_plugin_dir

algorithm_deplist=$(ldd $algorithm_plugin_dir/$algorithm_so | awk  '{if (match($3,"/")){ printf("%s "),$3 } }')
cp $algorithm_deplist $lib_dir

# 生成dep文件
cd $repo_build_dir;dpkg -b $1 P600_$1.deb

