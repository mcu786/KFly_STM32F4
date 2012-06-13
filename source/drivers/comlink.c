/* *
 *
 * Hardware Abstraction Layer for all comunication
 *
 * TODO:
 * Add support for Serial Communication AUX1, AUX2 and AUX3
 *
 * */


#include "comlink.h"

/* Gobal variable defines */
volatile xQueueHandle xUSBQueueHandle = NULL;
volatile Bool bUSBAvalible = FALSE;

/* Private function defines */

/* Private external functions */
extern uint16_t cdc_DataTx(uint8_t *, uint32_t);

/* *
 * vUSBQueueInit initializes the queue for USB recieved data
 * */
void vUSBQueueInit(void)
{
	xUSBQueueHandle = xQueueCreate(USBQueueSize, sizeof(uint8_t));
}


/* *
 *
 * Function for sending data over USB.
 * Theoretical max speed is 1.6Mbaud however a much slower rate is
 * recommened because the in and out endpoints uses the same buffer.
 *
 * */
ErrorStatus xUSBSendData(uint8_t *data, uint32_t size)
{
	vTaskSuspendAll();

	if (bUSBAvalible == FALSE)
	{
		/* USB is not avalible, signal with error. */
		xTaskResumeAll();
		return ERROR;
	}
	else
	{
		cdc_DataTx(data, size);
		xTaskResumeAll();
		return SUCCESS;
	}
}