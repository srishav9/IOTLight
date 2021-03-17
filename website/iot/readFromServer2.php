<?php
	$db_host = "localhost";
	$db_user = "laxus";
	$db_pass = "Laxus#1996";
	$db_name = "iot";
	$connect = mysqli_connect($db_host, $db_user, $db_pass, $db_name);
	if( mysqli_connect_errno($connect) ){
		echo "Failed to connect to MySQL: " . mysqli_connect_error();
		exit();
	}
	if( $result = mysqli_query($connect, "select * from room_two") ){
		$row = mysqli_fetch_assoc($result);
    echo $row['status_one'];
		echo $row['status_two'];
	}
	mysqli_close($connect);
?>
