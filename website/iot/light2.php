<?php
	$db_host = "localhost";
	$db_user = "laxus";
	$db_pass = "Laxus#1996";
	$db_name = "iot";
	$connect = mysqli_connect($db_host, $db_user, $db_pass, $db_name);
	if( mysqli_connect_errno($connect) )
	{
		echo "Failed to connect to MySQL: " . mysqli_connect_error();
		exit();
	}
	$task = $_REQUEST['query'];
  if($task == 'd1on'){
  	mysqli_query($connect,"update room_two set status_one='device_one_on'");
  }
  if($task == 'd1off'){
  	mysqli_query($connect,"update room_two set status_one='device_one_off'");
  }
	if($task == 'd2on'){
		mysqli_query($connect,"update room_two set status_two='device_two_on'");
	}
	if($task == 'd2off'){
		mysqli_query($connect,"update room_two set status_two='device_two_off'");
	}
	mysqli_close($connect);
?>
