<?php
/**
 * <--- Copyright 2005-2010 de Solis - Cooperativa de Solu��es Livres Ltda.
 *
 * Este arquivo � parte do programa Sagu.
 *
 * O Sagu � um software livre; voc� pode redistribu�-lo e/ou modific�-lo
 * dentro dos termos da Licen�a P�blica Geral GNU como publicada pela Funda��o
 * do Software Livre (FSF); na vers�o 2 da Licen�a.
 *
 * Este programa � distribu�do na esperan�a que possa ser �til, mas SEM
 * NENHUMA GARANTIA; sem uma garantia impl�cita de ADEQUA��O a qualquer MERCADO
 * ou APLICA��O EM PARTICULAR. Veja a Licen�a P�blica Geral GNU/GPL em
 * portugu�s para maiores detalhes.
 *
 * Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral GNU, sob o t�tulo
 * "LICENCA.txt", junto com este programa, se n�o, acesse o Portal do Software
 * P�blico Brasileiro no endere�o www.softwarepublico.gov.br ou escreva para a
 * Funda��o do Software Livre (FSF) Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA --->
 *
 * Basic file handler.
 * Contains the menus to access file registers
 *
 * @author Daniel Afonso Heisler [daniel@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Arthur Lehdermann [arthur@solis.coop.br]
 * Daniel Afonso Heisler [daniel@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 *
 * @since
 * Class created on 11/08/2005
 *
 **/

$MIOLO->trace('file:' . $_SERVER['SCRIPT_NAME']);
$home = 'main:config:file';
$navbar->addOption(_M('Arquivo', $module), $module, $home);
$MIOLO->getClass('basic', 'access');
access::insert(_M('Arquivo', $module), $home, 'file-16x16.png');
$data->home = $home;
$function = MIOLO::_request('function');
$ui = $MIOLO->getUI();
if ( (strlen($function) == 0) || ($function == 'search') )
{
    $MIOLO->checkAccess('FrmFile', A_ACCESS, true, true);
    $frmFileSearch = $ui->getForm($module,'FrmFileSearch', $data);
    $frmFileSearch->setClose($MIOLO->getActionURL($module,substr($home, 0, strrpos($home, ':'))));
    $content = $frmFileSearch;
    $theme->clearContent();
    $theme->insertContent($content);
}
else
{
    $backUrl = 'javascript:history.go(-1)';
    switch ( $function )
    {
        case 'download':
            $MIOLO->checkAccess('FrmFile', A_ACCESS, true, true);
        break;
        default:
            $MIOLO->error(_M('Fun��o desconhecida.', $module), $backUrl);
        break;
    }

    $fileId = MIOLO::_request('fileId');
    if ( strlen($fileId) <= 0 )
    {
        $MIOLO->error(_M('Identificador de arquivo inv�lido.', $module), $backUrl);
    }
    else
    {
        $business = new BusinessBasicBusFile();
        $data     = $business->getFile($fileId);
        if ( strlen($data->fileId) <= 0 )
        {
            $MIOLO->error(_M('Arquivo n�o registrado na base de dados.', $module), $backUrl);
        }
        else
        {            
            $business->getFileAsDownload($fileId,'application/octet-stream');
        }
    }
}
?>
