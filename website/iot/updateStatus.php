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
    $lockStatus = $_REQUEST['lock'];
    if( strcmp($lockStatus,"on")==0){
        mysqli_query($connect,"update digilock set lock_status=1");
    }
    if( strcmp($lockStatus,"off")==0){
        mysqli_query($connect,"update digilock set lock_status=0");
    }
    
    // if($result = mysqli_query("select * from room_one")){
    //     $row = mysqli_fetch_assoc($result);
    //     if((strcmp($row['status_one'],'device_one_on')==0) || (strcmp($row['status_two'],'device_two_one')==0))
    //     {
    //         echo "forgot";
            
    //     }
    // }
?>